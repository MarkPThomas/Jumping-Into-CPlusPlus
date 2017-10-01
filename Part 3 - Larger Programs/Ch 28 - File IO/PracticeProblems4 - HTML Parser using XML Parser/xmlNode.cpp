#include <map>
#include <vector>
#include "xmlNode.h"

using namespace std;

// Properties
char xmlNode::TagOpen() const
{
	return _tagOpen;
}

char xmlNode::CloseTagStart() const
{
	return _closeTagStart;
}

char xmlNode::TagClose() const
{
	return _tagClose;
}


string xmlNode::Name() const
{
	return _name;
}

vector<string> xmlNode::Attributes()
{
	vector<string> attributeKeys;
	for (map<string, string>::iterator itr = _attributes.begin(), end = _attributes.end(); 
		itr != end; 
		++itr) 
	{
		attributeKeys.push_back(itr->first);
	}
	return attributeKeys;
}

string xmlNode::AttributeValue(string attribute)
{
	return _attributes[attribute];
}

string xmlNode::InnerText() const
{
	return _innerText;
}

int xmlNode::NumberOfChildren() const
{
	return _children.size();
}

xmlNode* xmlNode::Child(int index)
{
	return _children[index];
}


// Constructors/Destructors
/// <summary>
/// Initializes a new instance of the <see cref="xmlNode"/> class using the default tag characters of &lt;, &gt;, &lt;\.
/// </summary>
xmlNode::xmlNode()
{
	_tagOpen = '<';
	_closeTagStart = '/';
	_tagClose = '>';
}

/// <summary>
/// Initializes a new instance of the <see cref="xmlNode"/> class with custom characters for defining tags and indicating a closing tag.
/// </summary>
/// <param name="tagOpen">The tag is opening.</param>
/// <param name="tagClose">The tag is closing.</param>
/// <param name="nodeClose">The opening tag is closing the node.</param>
xmlNode::xmlNode(char tagOpen, char tagClose, char nodeClose)
{
	_tagOpen = tagOpen;
	_tagClose = tagClose;
	_closeTagStart = nodeClose;
}

/// <summary>
/// Initializes a new instance of the <see cref="xmlNode"/> class as a text node.
/// </summary>
/// <param name="input">The input.</param>
xmlNode::xmlNode(const string& input) : xmlNode()
{
	_name = _textNode;
	_innerText = input;
}

xmlNode::~xmlNode()
{
	for (vector<xmlNode*>::iterator itr = _children.begin(), end = _children.end();
		itr != end;
		++itr)
	{
		delete *itr;
	}
	_children.clear();
}


// Methods
/// <summary>
/// Creates the node.
/// </summary>
/// <param name="input">The input stream. 
/// It is assumed that this has no preceding or trailing whitespace, that it starts and ends with tags, and that the tags properly close.</param>
/// <returns>xmlNode *.</returns>
xmlNode* xmlNode::createNode(const string& input)
{
	xmlNode* node = new xmlNode();
	node->nodeStart(input);
	return node;
}

xmlNode* xmlNode::createTextNode(const string& input)
{
	xmlNode* node = new xmlNode(input);
	return node;
}

/// <summary>
/// Fills in node data from the start tag until closing.
/// </summary>
/// <param name="nameNode">The input stream. 
/// It is assumed that this has no preceding or trailing whitespace, that it starts and ends with tags, and that the tags properly close.</param>
void xmlNode::nodeStart(const string& input)
{
	// Get start tag name & attributes if they exist
	int startTagOpenIndex = input.find_first_of(_tagOpen);
	int spaceIndex = input.find_first_of(' ', startTagOpenIndex);
	int startTagCloseIndex = input.find_first_of(_tagClose, startTagOpenIndex);
	if (spaceIndex != string::npos && spaceIndex < startTagCloseIndex)
	{
		_name = input.substr(startTagOpenIndex + 1, (spaceIndex - 1) - startTagOpenIndex);
		attributeRead(input.substr(spaceIndex + 1, (startTagCloseIndex - 1) - spaceIndex));
	}
	else
	{
		_name = input.substr(startTagOpenIndex + 1, (startTagCloseIndex - 1) - startTagOpenIndex);
	}

	// Get inner text
	string closeTag = nodeEnd(_name);
	int endTagOpenIndex = input.find_last_of(closeTag);
	string innerText = input.substr(startTagCloseIndex + 1, (endTagOpenIndex - 1) - startTagCloseIndex - (closeTag.length() - 1));
	nodeTextRead(innerText);
}

/// <summary>
/// Parses the attributes string and records attributes.
/// </summary>
/// <param name="attributesStream">The attributes steam.
/// It is assumed that this is in the format of: {attribute1}="{attribute value1}" {attribute2}="{attribute value2}" ... {attribute_n}="{attribute value_n}".</param>
void xmlNode::attributeRead(const string& attributesStream)
{
	string currentKey = "";
	string currentEntry = "";
	bool isInValue = false;
	for (int i = 0; i < attributesStream.length(); i++)
	{
		if (attributesStream[i] == '=')
			// Reaching end of attribute. Record attribute & prepare for value.
		{
			currentKey = currentEntry;
			currentEntry.clear();
		}
		else if (attributesStream[i] == '"' && !isInValue)
		{
			isInValue = true;
		}
		else if (attributesStream[i] == '"' && isInValue) 
			// Reaching end of value. Record attribute:value pair & reset.
		{
			isInValue = false;
			currentEntry = clearEmpty(currentEntry);
			_attributes[currentKey] = currentEntry;
			currentKey.clear();
			currentEntry.clear();
		}
		else if (attributesStream[i] != '=' && 
				 attributesStream[i] != '"' && 
				 !(attributesStream[i] == ' ' && !isInValue)) 
				 	// Records all characters that are not reserved. 
				 	// Ignores spaces that are not included within values.
		{
			currentEntry += attributesStream[i];
		}
	}
}

/// <summary>
/// Parses the inner text and records it.
/// Child nodes are created for any internal tags.
/// </summary>
/// <param name="innerText">The inner text.
/// It is assumed that this has no starting or ending tags, and that internal tags properly close.
/// Any tags are treated as indicating child nodes.</param>
void xmlNode::nodeTextRead(const string& innerText)
{
	if (innerText.empty()) { return; }
	int startTagOpenIndex = innerText.find_first_of(_tagOpen);
	if (startTagOpenIndex == string::npos) // There are no child nodes
	{
		_innerText = innerText;
		_innerText = clearEmpty(_innerText);
		return;
	}

	// Handle inner text, including all child nodes.
	if (startTagOpenIndex > 1)
	{
		/*_innerText += innerText.substr(0, startTagOpenIndex - 1);*/
		_innerText += innerText.substr(0, startTagOpenIndex);
	}
	int openTagCount = 0;
	int tagCount = 0;
	string innerInnerText;
	for (int i = startTagOpenIndex; i < innerText.length(); i++)
	{
		char currentCharacter = innerText[i];
		// Determine current tag balance & open/close status
		if (currentCharacter == _tagOpen)
		{
			tagCount++;
			if (innerText.length() > i + 1 && 
				innerText[i + 1] == _closeTagStart)
			{
				openTagCount--;
			}
			else
			{
				openTagCount++;
			}
		}
		else if (currentCharacter == _tagClose)
		{
			tagCount--;
		}
		
		// Record character
		if (openTagCount == 0 && 
			tagCount == 0 &&
			currentCharacter != _tagClose)
			// Append all characters that lie outside of any child nodes.
		{
			_innerText.push_back(currentCharacter);
		}
		else
			// Record all text that includes and is within child nodes.
		{
			innerInnerText.push_back(currentCharacter);
		}

		// Check if child nodes are to be created
		if (currentCharacter == _tagClose && 
			openTagCount == 0)
			// All open tags have just closed.
		{
			_children.push_back(createNode(innerInnerText));
			innerInnerText.clear();
		}
		else if (currentCharacter == _tagOpen &&
				openTagCount == 0 &&
				!_innerText.empty())
			// A new tag is being opened
		{
			_innerText = clearEmpty(_innerText);
			if (_innerText.empty()) { continue; }
			_children.push_back(createTextNode(_innerText));
			_innerText.clear();
		}
	}
	_innerText = clearEmpty(_innerText);
}


string xmlNode::nodeEnd(const string& nameNode) const
{
	string nodeEndTag;
	nodeEndTag.push_back(_tagOpen);
	nodeEndTag.push_back(_closeTagStart);
	return (nodeEndTag + nameNode + _tagClose); 
}


string xmlNode::print(xmlNode* node, int indentLevel, const string& spacer)
{
	// Set indentation
	string currentSpacer;
	spacer.empty() ? currentSpacer = _spacer : currentSpacer = spacer;
	string tabs = getTabs(indentLevel, currentSpacer);

	// Create opening tag
	string currentNode = printOpeningTag(node, tabs);

	// Add inner text 
	currentNode += printInnerText(node, tabs, currentSpacer);

	// Add any child nodes
	int children = node->NumberOfChildren();
	for (int i = 0; i < children; i++)
	{
		currentNode += printChildNodes(node, i, indentLevel);
	}

	// Add closing tag
	currentNode += printClosingTag(node, tabs);

	return currentNode;
}

string xmlNode::printOpeningTag(xmlNode* node, const string& tabs)
{
	string currentNode = tabs;
	currentNode.push_back(_tagOpen);
	currentNode += node->Name();
	// Add attributes to opening tag
	vector<string> attributes = node->Attributes();
	for (vector<string>::iterator itr = attributes.begin(), end = attributes.end();
		itr != end;
		++itr)
	{
		currentNode += " " + *itr + "=\"" + node->AttributeValue(*itr) + "\"";
	}
	currentNode += _tagClose;
	return currentNode;
}

string xmlNode::printClosingTag(xmlNode* node, const string& tabs)
{
	string currentNode = '\n' + tabs;
	currentNode += nodeEnd(node->Name());
	return  currentNode;
}

string xmlNode::printInnerText(xmlNode* node, const string& tabs, const string& currentSpacer)
{
	string currentNode;
	if (!node->InnerText().empty())
	{
		currentNode += '\n' + tabs + currentSpacer;
		currentNode += node->InnerText();
	}
	return currentNode;
}

string xmlNode::printChildNodes(xmlNode* node, int childIndex, int indentLevel)
{
	string currentNode;
	currentNode += '\n';
	currentNode += print(node->Child(childIndex), indentLevel + 1);
	return currentNode;
}


string xmlNode::clearEmpty(string& text)
{
	if (text.find_first_not_of(' ') == string::npos)
	{
		return "";
	}
	if (text.find_first_not_of('\t') == string::npos)
	{
		return "";
	}
	return text;
}

string xmlNode::getTabs(int indentationLevel, const string& spacer) const
{
	string tabs = "";
	string currentSpacer;
	spacer.empty() ? currentSpacer = _spacer : currentSpacer = spacer;
	for (int i = 0; i < indentationLevel; i++)
	{
		tabs += currentSpacer;
	}
	return tabs;
}

#include "htmlPrinter.h"
#include <string>

using namespace std;

// Methods
/// <summary>
/// Creates the node.
/// </summary>
/// <param name="xmlDOMStream">The input stream. 
/// It is assumed that this has no preceding or trailing whitespace, that it starts and ends with tags, and that the tags properly close.</param>
/// <returns>xmlNode *.</returns>
htmlPrinter* htmlPrinter::createNode(const string& xmlDOMStream)
{
	htmlPrinter* node = new htmlPrinter(xmlDOMStream);
	return node;
}

htmlPrinter::htmlPrinter(const string& xmlDOMStream)
{
	nodeStart(xmlDOMStream);
}


string htmlPrinter::print(xmlNode* node, int indentLevel, const string& spacer)
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

string htmlPrinter::printOpeningTag(xmlNode* node, const string& tabs)
{
	string currentNode;
	if (node->Name() == _textNode)
	{
		return "";
	}
	if (node->Name() == "html")
	{
		return "";
	}
	if (node->Name() == "html")
	{
		return "";
	}
	if (node->Name() == "br")
	{
		return "";
	}
	if (node->Name() == "a")
	{
		return "";
	}
	if (node->Name() == "ul")
	{
		return "\n";
	}
	if (node->Name() == "ol")
	{
		return "\n";
	}
	if (node->Name() == "li")
	{
		return "";
	}
	if (node->Name() == "b")
	{
		return "*";
	}
	if (node->Name() == "i")
	{
		return "_";
	}
	if (node->Name() == "body")
	{
		currentNode = "\n" + tabs;
		currentNode.push_back(TagOpen());
		currentNode += node->Name() + TagClose() + '\n';
		return currentNode;
	}
	return xmlNode::printOpeningTag(node, tabs);
}

string htmlPrinter::printClosingTag(xmlNode* node, const string& tabs)
{
	if (node->Name() == _textNode)
	{
		return "";
	}
	if (node->Name() == "html")
	{
		return "";
	}
	if (node->Name() == "br")
	{
		return "";
	}
	if (node->Name() == "a")
	{
		return "";
	}
	if (node->Name() == "ul")
	{
		return "";
	}
	if (node->Name() == "ol")
	{
		return "";
	}
	if (node->Name() == "li")
	{
		return "";
	}
	if (node->Name() == "b")
	{
		return "*";
	}
	if (node->Name() == "i")
	{
		return "_";
	}
	return xmlNode::printClosingTag(node, tabs);
}

string htmlPrinter::printInnerText(xmlNode* node, const string& tabs, const string& currentSpacer)
{
	if (node->Name() == _textNode)
	{
		return node->InnerText();
	}
	if (node->Name() == "head")
	{
		return "";
	}
	if (node->Name() == "br")
	{
		return "\n";
	}
	if (node->Name() == "b")
	{
		return node->InnerText();
	}
	if (node->Name() == "i")
	{
		return node->InnerText();
	}
	if (node->Name() == "ul")
	{
		return "";
	}
	if (node->Name() == "ol")
	{
		return "";
	}
	if (node->Name() == "li")
	{
		return node->InnerText() + '\n';
	}
	if (node->Name() == "a")
	{
		return node->InnerText() + '(' + node->AttributeValue("href") + ')';
	}
	return xmlNode::printInnerText(node, tabs, currentSpacer);
}

string htmlPrinter::printChildNodes(xmlNode* node, int childIndex, int indentLevel)
{
	string currentNode;
	xmlNode* childNode = node->Child(childIndex);
	if (node->Name() == _textNode)
	{
		return "";
	}
	if (node->Name() == "html")
	{
		return print(childNode, indentLevel + 1);
	}
	if (node->Name() == "head")
	{
		return "";
	}
	if (node->Name() == "b")
	{
		return print(childNode);
	}
	if (node->Name() == "i")
	{
		return print(childNode);
	}
	if (node->Name() == "a")
	{
		return print(childNode);
	}
	if (node->Name() == "ul" &&
		childNode->Name() == "li")
	{
		string tabs = getTabs(indentLevel, _spacer);
		currentNode += tabs;
		currentNode += "* ";
		currentNode += print(childNode, indentLevel + 1);
		return currentNode;
	}
	if (node->Name() == "ol" &&
		childNode->Name() == "li")
	{
		string tabs = getTabs(indentLevel, _spacer);
		currentNode += tabs;
		currentNode += to_string(childIndex + 1) + ". ";
		currentNode += print(childNode, indentLevel + 1);
		return currentNode;
	}
	
	currentNode += print(childNode, indentLevel + 1);
	return currentNode;
}
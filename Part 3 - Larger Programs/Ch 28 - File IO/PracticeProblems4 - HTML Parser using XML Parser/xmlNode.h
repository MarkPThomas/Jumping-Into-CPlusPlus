#pragma once
#include <map>
#include <vector>
class xmlNode
{
public:
	// Properties
	char TagOpen() const;
	char CloseTagStart() const;
	char TagClose() const;
	std::string Name() const;
	std::vector<std::string> Attributes();
	std::string AttributeValue(std::string attribute);
	std::string InnerText() const;
	int NumberOfChildren() const;
	xmlNode* Child(int index);

	// Constructor/destructors
	xmlNode();
	xmlNode(const std::string& input);
	xmlNode(char tagOpen, char tagClose, char nodeClose);
	virtual ~xmlNode();

	// Methods
	static xmlNode* createNode(const std::string& input);
	void nodeStart(const std::string& input);
	virtual std::string print(xmlNode* node, int indentLevel = 0, const std::string& spacer = "");
protected:
	const std::string xmlNode::_spacer = "  ";
	const std::string xmlNode::_textNode = "#text";

	virtual std::string printOpeningTag(xmlNode* node, const std::string& tabs = "");
	virtual std::string printClosingTag(xmlNode* node, const std::string& tabs = "");
	virtual std::string printInnerText(xmlNode* node, const std::string& tabs = "", const std::string& currentSpacer = "");
	virtual std::string printChildNodes(xmlNode* node, int childIndex, int indentLevel);

	std::string nodeEnd(const std::string& nameNode) const;
	std::string getTabs(int indentationLevel, const std::string& spacer = "") const;
private:
	char _tagOpen;
	char _closeTagStart;
	char _tagClose;
	std::string _name;
	std::map<std::string, std::string> _attributes;
	std::vector<xmlNode*> _children;
	std::string _innerText;

	static xmlNode* createTextNode(const std::string& input);
	void attributeRead(const std::string& attributesStream);
	void nodeTextRead(const std::string& innerText);
	static std::string clearEmpty(std::string& text);
};

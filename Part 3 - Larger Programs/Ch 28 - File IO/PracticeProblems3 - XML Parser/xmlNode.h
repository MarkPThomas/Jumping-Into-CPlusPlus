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
	xmlNode(char tagOpen, char tagClose, char nodeClose);
	~xmlNode();

	// Methods
	static xmlNode* createNode(const std::string& input);
	void nodeStart(const std::string& input);
	std::string print(int level = 0, const std::string& spacer = "");
private:
	const std::string xmlNode::_spacer = "  ";

	char _tagOpen;
	char _closeTagStart;
	char _tagClose;
	std::string _name;
	std::map<std::string, std::string> _attributes;
	std::vector<xmlNode*> _children;
	std::string _innerText;

	void attributeRead(const std::string& attributesStream);
	void nodeTextRead(const std::string& innerText);
	std::string nodeEnd(const std::string& nameNode) const;
	static std::string clearEmpty(std::string& text);
};

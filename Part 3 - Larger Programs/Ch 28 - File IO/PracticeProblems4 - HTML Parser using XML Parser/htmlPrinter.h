#pragma once
#include "xmlNode.h"

class htmlPrinter : public xmlNode
{
public:
	htmlPrinter(const std::string& xmlDOMStream);

	static htmlPrinter* createNode(const std::string& input);
	//std::string print(int level = 0, const std::string& spacer = "") override;
	std::string print(xmlNode* node, int indentLevel = 0, const std::string& spacer = "") override;
protected:
	std::string printOpeningTag(xmlNode* node, const std::string& tabs = "") override;
	std::string printClosingTag(xmlNode* node, const std::string& tabs = "") override;
	std::string printInnerText(xmlNode* node, const std::string& tabs = "", const std::string& currentSpacer = "") override;
	std::string printChildNodes(xmlNode* node, int childIndex, int indentLevel) override;
private:
	xmlNode* _root;
};

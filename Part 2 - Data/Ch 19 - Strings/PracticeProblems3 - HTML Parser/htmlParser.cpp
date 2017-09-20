#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const vector<string>& input);
vector<string> parseHTMLStringToVector(const string& htmlDOMStream);
vector<string> mergeChildElements(const vector<string>& input, const string& tagName);
vector<string> stripTag(const vector<string>& input, const string& tagName);
vector<string> stripTagAttributes(const vector<string>& input, const string& tagName);
vector<string> stripText(const vector<string>& input, const string& tagName);
vector<string> substituteTag(const vector<string>& input, const string& tagName, const string& tagNameSubstitute);
vector<string> formatBold(const vector<string>& input);
vector<string> formatItalic(const vector<string>& input);
vector<string> formatHyperlink(const vector<string>& input);
string getLinkURL(const string& hrefTag);

const string openTagStart = "<";
const string closeTagStart = "</";
const string tagEnd = ">";

int main()
{
	string htmlDOMStream = "<html xmlns=\"http://www.w3.org/1999/xhtml\" itemscope=\"\" itemtype=\"http://schema.org/WebPage\">";
		htmlDOMStream += "<head>";
		htmlDOMStream += "<meta property=\"og : image\" content=\"https ://lh3.googleusercontent.com/-mln6PaqJChw/UOIaqjWmkgI/AAAAAAABno0/sck_C8SCr-0/s240/DSCN6032a.jpg\" />";
		htmlDOMStream += "<script type=\"text / javascript\">";
		htmlDOMStream += "  window.jstiming.load.tick('cl');";
		htmlDOMStream += "</script>";
		htmlDOMStream += "</head>";
		htmlDOMStream += "<body xmlns=\"http://www.google.com/ns/jotspot\" id=\"body\" class=\" en            \">";
		htmlDOMStream += " This is an html text file that is parsed to handle text such as <b>bold text</b>, <i>italic text</i>, and even <a href=\"www.google.com\">hyperlink text</a>.";
		htmlDOMStream += "</body>";
		htmlDOMStream += "</html>";

	vector<string> htmlDOM = parseHTMLStringToVector(htmlDOMStream);
	const string body = "body";

	cout << "Original HTML: \n";
	vector<string> htmlDOMPrint = mergeChildElements(htmlDOM, body);
	print(htmlDOMPrint);

	// Ignore the tag:
	const string html = "html";
	htmlDOM = stripTag(htmlDOM, html);

	// Remove text within this tag:
	const string head = "head";
	htmlDOM = stripText(htmlDOM, head);

	// Display all text within the body tag:
	htmlDOM = stripTagAttributes(htmlDOM, body);
	htmlDOM = formatBold(htmlDOM);
	htmlDOM = formatItalic(htmlDOM);
	htmlDOM = formatHyperlink(htmlDOM);

	cout << "Parsed HTML:\n";
	htmlDOMPrint = mergeChildElements(htmlDOM, body);
	print(htmlDOMPrint);
}

void print(const vector<string>& input)
{
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		cout << *itr << endl;
	}
	cout << '\n';
}

vector<string> mergeChildElements(const vector<string>& input, const string& tagName)
{
	string openingTag = openTagStart + "body";	// tagEnd is left off to allow matches for tags with various attributes.
	string closingTag = closeTagStart + "body" + tagEnd;
	bool isInMergeRegion = false;
	
	vector<string> output;
	string currentMerge;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		string itrOpening = itr->substr(0, openingTag.length());
		if (itrOpening == openingTag)
		{
			isInMergeRegion = true;
			output.push_back(*itr);
		}
		else if (isInMergeRegion &&
			*itr == closingTag)
		{
			isInMergeRegion = false;
			if (currentMerge != "")
			{
				output.push_back(currentMerge);
			}
			output.push_back(*itr);
		}
		else if (isInMergeRegion)
		{
			currentMerge += *itr;// +" ";
		}
		else
		{
			output.push_back(*itr);
		}
	}
	return output;
}

vector<string> parseHTMLStringToVector(const string& htmlDOMStream)
{
	bool isInOpenTag = false;
	bool isInCloseTag = false;

	vector<string> htmlDOM;
	string currentEntry = "";

	// Change to new entry when:
	// 1. Entering an opening tag
	// 2. Leaving an opening tag
	// 3. Entering a closing tag
	// 4. Leaving a closing tag
	for (int i = 0; i < htmlDOMStream.length(); i++)
	{
		string currentLetter(1, htmlDOMStream[i]);
		
		string previousLetter;
		if (i - 1 >= 0)
		{
			previousLetter.push_back(htmlDOMStream[i-1]);
		}
		
		string nextLetter;
		if (i + 1 < htmlDOMStream.length())
		{
			nextLetter.push_back(htmlDOMStream[i + 1]);
		}

		if(currentLetter == openTagStart)
		{
			isInOpenTag = true;
			if (currentEntry != "")
			{
				htmlDOM.push_back(currentEntry);
			}
			currentEntry = htmlDOMStream[i];
		}
		else if (currentLetter + nextLetter == closeTagStart)
		{
			isInCloseTag = true;
			htmlDOM.push_back(currentEntry);
			currentEntry = htmlDOMStream[i];
		}
		else if (isInOpenTag && 
			previousLetter == tagEnd)
		{
			isInOpenTag = false;
			htmlDOM.push_back(currentEntry);
			currentEntry = htmlDOMStream[i];
		}
		else if (isInCloseTag &&
			currentLetter == tagEnd)
		{
			isInCloseTag = false;
			currentEntry += htmlDOMStream[i];

			htmlDOM.push_back(currentEntry);
			currentEntry = "";
		}
		else
		{
			currentEntry += htmlDOMStream[i];
		}
	}
	return htmlDOM;
}

/// <summary>
/// Strips the HTML tag from the input.
/// Inner tags and text are left untouched.
/// </summary>
/// <param name="input">The input.</param>
/// <param name="tagName">Name of the tag.</param>
/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
vector<string> stripTag(const vector<string>& input, const string& tagName)
{
	string openingTag = openTagStart + tagName;	// tagEnd is left off to allow matches for tags with various attributes.
	string closingTag = closeTagStart + tagName + tagEnd;
	bool isInStripRegion = false;

	vector<string> output;
	for(vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		string itrOpening = itr->substr(0, openingTag.length());
		if (!isInStripRegion &&
			itrOpening == openingTag)
		{
			isInStripRegion = true;
		}
		else if (isInStripRegion &&
			*itr == closingTag)
		{
			isInStripRegion = false;
		}
		else
		{
			output.push_back(*itr);
		}
	}
	return output;
}

/// <summary>
/// Strips all attributes in the HTML tag.
/// </summary>
/// <param name="input">The input.</param>
/// <param name="tagName">Name of the tag.</param>
/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
vector<string> stripTagAttributes(const vector<string>& input, const string& tagName)
{
	string openingTag = openTagStart + tagName;	// tagEnd is left off to allow matches for tags with various attributes.

	vector<string> output;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		string itrOpening = itr->substr(0, openingTag.length());
		if (itrOpening == openingTag)
		{
			output.push_back(openingTag + tagEnd);
		}
		else
		{
			output.push_back(*itr);
		}
	}
	return output;
}

/// <summary>
/// Strips the text from within the specified HTML tag from the input.
/// </summary>
/// <param name="input">The input.</param>
/// <param name="tagName">Name of the tag.</param>
/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
vector<string> stripText(const vector<string>& input, const string& tagName)
{
	string openingTag = openTagStart + tagName; // tagEnd is left off to allow matches for tags with various attributes.
	string closingTag = closeTagStart + tagName + tagEnd;
	bool isInStripRegion = false;

	vector<string> output;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		string itrOpening = itr->substr(0, openingTag.length());
		if (!isInStripRegion &&
			itrOpening == openingTag)
		{
			isInStripRegion = true;
			output.push_back(*itr);
		}
		else if (isInStripRegion &&
			*itr == closingTag)
		{
			isInStripRegion = false;
			output.push_back(*itr);
		}
		else if (!isInStripRegion)
		{
			output.push_back(*itr);
		}
	}
	return output;
}

vector<string> formatBold(const vector<string>& input)
{
	// Define bold with *:
	return substituteTag(input, "b", "*");
}

vector<string> formatItalic(const vector<string>& input)
{
	// Define italic with _:
	return substituteTag(input, "i", "_");
}

vector<string> substituteTag(const vector<string>& input, const string& tagName, const string& tagNameSubstitute)
{
	string openingTag = openTagStart + tagName + tagEnd;
	string closingTag = closeTagStart + tagName + tagEnd;

	vector<string> output;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		if (*itr == openingTag ||
			*itr == closingTag)
		{
			output.push_back(tagNameSubstitute);
		}
		else
		{
			output.push_back(*itr);
		}
	}
	return output;
}

vector<string> formatHyperlink(const vector<string>& input)
{
	// Define hyperlink as linkText(linkURL):
	const string hyperlink = "a";
	bool insidetag = false;

	string openingTag = openTagStart + hyperlink;
	string closingTag = closeTagStart + hyperlink + tagEnd;

	vector<string> output;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		string itrOpening = itr->substr(0, openingTag.length());
		if (itrOpening == openingTag)
		{
			insidetag = true;

			// Get link URL
			string linkURL = getLinkURL(*itr);

			// Get inner text
			vector<string>::const_iterator next = itr;
			++next;
			string innerText = *next;

			output.push_back(innerText + "(" + linkURL + ")"); 
		}
		else if (*itr == closingTag)
		{
			insidetag = false;
		}
		else if (!insidetag)
		{
			output.push_back(*itr);
		}
	}
	return output;
}

string getLinkURL(const string& hrefTag)
{
	const string hyperlinkURL = "href=";
	int position = hrefTag.find(hyperlinkURL, 0) + hyperlinkURL.length();
	
	string linkURL = "";
	char endDemaractor;
	if (hrefTag[position] == '\"')
	{
		endDemaractor = '\"';
		position++;
	}
	else
	{
		endDemaractor = ' ';
	}

	for (int i = position; i < hrefTag.length(); i++)
	{
		if (hrefTag[i] == endDemaractor)
		{
			break;
		}
		linkURL += hrefTag[i];
	}
	return linkURL;
}

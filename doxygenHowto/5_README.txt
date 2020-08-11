Doxygen 1.8.0 onwards supports Markdown support.
Ie using simple text as markup which appears distinctly in the documentation.

Examples:

-------------------------------------------------------------------
Paragraphs: just put an empty blank line and doxygen will treat it as a new paragraph
-------------------------------------------------------------------
Headers: doxygen supports upto 6 levels of headers. Preceed a header with that many #. Example

# Level 1 header
## Level 2 header
-------------------------------------------------------------------
block quote each line of a block quote must start with atleast one > sign.
> This is a block quote
> spanning multiple lines
-------------------------------------------------------------------
lists. simple bullet lists can be specified using -, +, or *. You can any of these three. List items can also be nested

- Item 1

    More detailed text for item 1 (must have blank line up and below)

- Item 2
   + Nested Item 2 first value
   + Nested Item 2 second value
- Item 3
- Item 4
   + Nested Item 4 first value
   + Nested Item 4 second value

-# Numbered list 1

   - Nested list inside a numbered list
   - Nested list inside a numbered list

-# Numbered list 2
-------------------------------------------------------------------

Code blocks : A paragraph with 4 spaces at the beginning is considered a code block. Example:

First paragraphs

    int main() { return 0};
    auto&& tmp = make_auto(SVar);

Second paragraph
-------------------------------------------------------------------
Links: doxygen provides inline links and reference links
inline links:
[The link text](http://example.net/ "Link title")
[The link text](/relative/path/to/index.html "Link title")
[The link text](somefile.html)
[The link text](@ref MyClass)  --> where MyClass is some documented entity.

reference links:
where you define the link first and can refer it multiple times in your documentation. Example:

[link name]: http://www.example.com "Optional title"
then later

[the link text][link name]
---------------------------------------------------------------------
See this link for more.
https://www.doxygen.nl/manual/markdown.html

Another important link to view special commands in doxygen:
https://www.doxygen.nl/manual/commands.html

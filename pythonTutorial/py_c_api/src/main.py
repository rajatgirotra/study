# import re
import sys
# from bs4 import BeautifulSoup
# import requests

# def extract_content(url):
#     """Given a URL, extract all the text content,
#     save it to a text file and return the number of
#     words that have been processed.
#     """
#
#     webpage = requests.get(url)
#     soup = BeautifulSoup(webpage.content, "lxml")
#     content = soup.find("body").findAll("p")
#     count = 0
#
#     with open("content.txt", "w") as file:
#         for paragraph in content:
#             text = paragraph.get_text()
#             words = re.findall(r'\b\w+', text)
#             file.write(text)
#             count += len(words)
#
#     return count

if __name__ == '__main__':
    print(sys.argv)
    # print("\n--- entering python script ---")
    # url = sys.argv[1]
    # count = extract_content(url)
    # print("{} words have been saved to './content.txt'".format(count))
    # print("--- exiting python script ---\n")
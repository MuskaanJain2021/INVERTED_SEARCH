# InvertedSearch

## Overview

**InvertedSearch** is a powerful tool designed to optimize search functionality by utilizing an inverted index data structure. This approach enables rapid full-text searches by mapping words to their locations within a set of documents. Instead of scanning every document, the system uses an index to quickly locate relevant files, significantly improving search speed and efficiency.

## Goals

- **Optimize Search Performance:** By creating an efficient inverted index, the system reduces the time and resources needed to find documents that contain specific words.
- **Enable Fast Querying:** Implement a robust querying mechanism that provides quick results by leveraging the pre-built index.
- **Maintain Flexibility:** Allow for easy updating of the index as files are added or removed from the database.

## Prerequisites

- **Hashing:** Understanding of hash tables for efficient data retrieval.
- **Single Linked List:** Basic knowledge of linked lists for storing and managing index data.

## Complexity Level

- **Complex**

## Introduction

An inverted index maps content (such as words) to its locations in a database or set of documents, allowing for rapid full-text searches. This data structure is fundamental in search engines and document retrieval systems. While building the index involves some overhead, it greatly enhances search query performance.

## Features

- **Indexing:** Create and maintain an index of words from a set of files.
- **Searching:** Efficiently query the indexed data to find relevant documents based on user input.

## Design

### Module 1: Indexing

**File1: `Main_Indexing.c`**
- **Purpose:** The entry point for the indexing process.
- **Key Function:** Initializes the indexing process by reading the list of files and creating/updating the index file.
  
  
  int main(int argc, char** argv);
  

**File2: `Indexing.c`**
- **Purpose:** Handles the creation and updating of the index.
- **Key Functions:**
  - **`create_database(FILE* FileList)`**: Reads file names from `FileList` and initiates indexing.
  - **`read_datafile(FILE* file, Word* WordList, char* filename)`**: Parses the file to extract words and update the index.
  - **`store_word(char* word, char* filename, Word* WordList)`**: Inserts words into a sorted linked list, associating them with file names.
  - **`write_databasefile(Word* WordList, FILE* Databasefile)`**: Writes the sorted index list to `DatabaseFile`.

### Module 2: Searching

**File1: `Main_Searching.c`**
- **Purpose:** Manages the search process based on user input.
- **Key Function:** Collects user queries and invokes searching mechanisms to retrieve and display relevant documents.

**File2: `Searching.c`**
- **Purpose:** Executes the search operations.
- **Key Functions:**
  - **`create_indexlist(FILE* Index_file, Word* Index_List)`**: Reads the index file into a linked list for efficient searching.
  - **`input_from_user()`**: Collects and processes user search input.
  - **`string_token(char* input_string)`**: Tokenizes the input string into words.
  - **`Search(char* word, Word* IndexList, File* Output_list)`**: Searches for each word in the index and updates the result list.
  - **`display_output(File* Output_list)`**: Displays the files with the highest match counts.

## Getting Started

1. **Indexing:**
   - Prepare a `FileList` containing the paths to the files you want to index.
   - Run `Main_Indexing.c` to generate or update the `DatabaseFile` with the indexed data.

2. **Searching:**
   - Run `Main_Searching.c` to start the search process.
   - Enter your search query, and the program will display files with the highest relevance based on the indexed data.

## References

1. [Inverted Index - Wikipedia](https://en.wikipedia.org/wiki/Inverted_index)
2. [Stanford IR Book - Building an Inverted Index](https://nlp.stanford.edu/IR-book/html/htmledition/a-first-take-at-building-an-inverted-index-1.html)
3. [IJCSI - Inverted Index](https://www.ijcsi.org/papers/IJCSI-8-4-1-384-392.pdf)
4. [ElasticSearch - Inverted Index](https://www.elastic.co/guide/en/elasticsearch/guide/current/inverted-index.html)
5. [Quora - Information Retrieval and Inverted Index](https://www.quora.com/Information-Retrieval-What-is-inverted-index)



## Contact

For any questions or feedback, please reach out to muskaanembed2023@gmail.com.


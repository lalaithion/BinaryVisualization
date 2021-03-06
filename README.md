# Binary Visualization Tool

## Contributors
Alex Curtiss - apccurtiss

Audrey Randall - Audrey-Randall

Izaak Weiss - lalaithion

Josh Anderson - janderso1337

## Final Presentation

https://docs.google.com/presentation/d/1yicXNmj51kbl1uZ3upRcpRAvd50egTqy4o6fNWzYo7M/edit?usp=sharing

## Description
This tool allows for the visualization of raw binary data in a way that uses the patterns inherent within structured data to identify the information it contains. Here is the ted talk which introduced the idea to us https://youtu.be/cWpRxyqDgpM?t=451, and here is a paper talking more about the same subject http://lib.dr.iastate.edu/cgi/viewcontent.cgi?article=4138&context=etd. This tool does not use headers or file extensions.

Our goal initially will be to create a working prototype in C++ using OpenGL. Then, depending on how much time we have left, we will explore creating an desktop application (on some or all of the major platforms) or a web app.

This tool could be used for applications such as data mining, packet analysis and malware detection.

## Vision Statement
Ever wanted to look like a hacker, but sadly the movies always look cooler than what you actually do? This tool is both useful for looking at data and super sweet.

## Motivation
We've seen examples in papers and a TED Talk, but have not been able to find a place where this software is available, and we would like to make it so.

##To build: Please see final submission.pdf

## Risks
### Testing
* Lack of reliable testing data
  * Solution: Create our own
* Possibility that the results are not as clear as others have claimed
  * Solution: Live with it

### OpenGL
* Only one of our team knows OpenGL, so we need to make sure that we can learn that library
  * Solution: That member of the team can teach the rest of us

### Scope
* Underestimating the scope of the project may end with us aiming too high
  * Solution: Take this into account when setting deadlines
* We may run into issues if we want to make this app work on all platforms
  * Solution: Make a webapp if it's too hard


### Other
* The government may notice our work and flag it as hacking related
  * Solution: Pray

## Requirements

### User Requirements
* 1. As a user I would like a graphical interface to easily manipulate the program with
  * 8 hours
* 2. As a user, I would like to have a file uploading feature so I can run the program on arbitrary binaries
  * 1 hour
* 3. As a user, I would like the product to generate a visual representation of a binary file to anaylze 
  * 8 hours
* 4. As a user, I want saving capabilities to store my requirements
  * 1 hour

### Functional Requirements
* 5. As a programmer, I'd like the program to be able to load binary data so that it could be visually encoded
  * 3 hours
* 6. As a programmer, I'd like to render the image in OpenGL to allow for fast rendering
  * 8 hours
* 7. As a programmer, I'd like to format the binary data with C++ because it is the fastest language with which I am most familier

### Non-Functional Requirements
* 8. As a user I'd like a compact UI to make it easier to interact with the program
  * 4 hours
* 9. As a l33t h4x0r I'd like it to look sweet, like movie hacking, so I can look aw3s0m3!
  * 3 hours
  

###Methodology
* We will be using a combination of Agile and Waterfall methodologies
* We will be using Trello to track our progress, at https://trello.com/b/1oGbTCzA/binaryvisualization

##Testing
* Our testing data, including TESTING.md, all of our screenshots and our pdfs are located in the TESTING directory
##Links
http://www.rumint.org/gregconti/publications/2008_VizSEC_FileVisualization_v53_final.pdf
http://www.rumint.org/gregconti/publications/taxonomy-bh.pdf

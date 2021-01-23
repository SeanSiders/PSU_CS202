Sean Siders
CS 202
11/20/2020
Program 4 & 5 : Online Media System Design
---
---
# Media Hierarchy
### Media : *Abstract Super Class*
---
##### Members
- Media author
- Creation time stamp
- Media title
- Media type : *final String*
- Due date

Any form of media that is in this system will be derived from this abstract super class. This media is targeted to teach students content related to a particular **Course**, and is presented in a linear fashion with the help of a **Playlist**. This media can take the form of a **Video**, **QuizVideo**, **Forum**, **Quiz**, or **Embed**, each of which have their own unique interactive learning features. Upon creating a form of media in the system, an *author* and *time stamp* will be recorded. Each sub class of **Media** will have final string member that describes the *type* of media this is. All media can either be manually created, or read in from an external file.

### Video : *Derived from **Media***
---
##### Members
- Video Length
- Closed Captioning
- Comments : **Thread** of **AuthoredText**

Students can watch a video and create a discussion about the content using the comments section.

### QuizVideo : *Derived from **Video***
---
##### Members
- Questions : **Thread** of **Questions**
- Question time stamps and keys (list of video times for each quiz question, and their respective keys to retrieve from **Thread**)

These videos will have predetermined questions that prompt at a particular time during the video. This is either determined by the author or the external file that contained this data. As the video plays, the current play time will be continuously checked. When a question time stamp occurs, the cooresponding question key will be used to retrieve the right question from the **Thread** data structure. From here the student will be prompted for input, followed by a check to the correct answer, prompting the student with their results.

### Forum : *Derived from **Media***
---
##### Members
- Forum discussion topic and description
- Discussions : **Thread** of **AuthoredText**

The author can create a forum, otherwise known as a discussion thread, where a topic or question is presented. Students will then engage in a threaded discussion about the provided topic.

### Quiz : *Derived from **Media***
---
##### Members
- Quiz questions : **Thread** of **Questions**

The author can create a quiz, with any number of questions in regards to class content. Along with each **Question**, will be a variety of correct answer keys and a description of the correct answer. Students will then input their answers into their own **Quiz**, where answers are internally recorded for each question. Upon the author's request, all quizzes will publish graded results to the students. An option for the teacher to override the automated grading will be an option as well.

### Embed : *Derived from **Media***
---
- HTML Embed code

A gateway of endless possiblities... In theory. The author can create any variety of external online resources that can be embeded with html, yay!

### Course : *derived from **Channel***
---
##### Members
- Course Title
- **Playlist** of *unpublished drafts*

When a course is made with this online resource, a **Course** will be created. Every **Course** is also a **Channel** which is the database for all learning related media in the course. The author of the course (typically referred to as the teacher) will have the ability to draft out media using a contained **Playlist**. The author can then choose to publish any media in the *draft playlist* manually to the **Channel**. From this published **Channel**, students will consume and interact with the media and learn so much.

### AuthoredText
---
##### Members
- Text Author
- Time stamp of creation
- Time stamp of last edit
- *String* of text

Any form of text content will be of type **AuthoredText**. This can take the form of a comment, description, or even a **Question** from a **Quiz** or **QuizVideo**. Any **AuthoredText** can be edited, which will be time stamped accordingly.

### Question : *Derived from **AuthoredText***
---
##### Members
- Array of correct answer key(s)
- Student answer
- Answer description

A student can be asked a question in two different contexts. The first context is through a **QuizVideo**, where the student will be prompted to answer a single question at a time. Immediate results will be displayed to the student as to their success or failure, which is determined through a check of all of the possible *answer keys*, provided by the author at the time of creation. To follow this, a description of the correct answer which is also determined by the author at the time of creation will be displayed. In the second context, the **Quiz** will store the student's answer in this **Question**, which will later be determined as correct or incorrect. **Quiz** will have a procedure that will delegate this process to all **Questions** that exist in that **Quiz**.

# Data Structures

### **Tree** : *binary search tree of courses*
---
##### Members
- **TreeNode** *root*

This binary search tree is the top level data structure, allowing for any number of courses to be managed by the system. Courses will be inserted by the key value of the course name, since there is no possiblity that there are duplicate course names. Teachers will have access to their own respective courses, and only the system admin should have access to the tree's operations, adding, removing, and editing courses. 

### **Tree** : *binary search tree of courses*
---
##### Members
- **TreeNode** *left child*
- **TreeNode** *right child*

### **Thread** : *List of **AuthoredText***
---
##### Members
- **ThreadNode** *head*
- **ThreadNode** *tail*

Any collection of text will be managed by **Thread**, which can be in the context of **Video** comments, a **Forum**, or even a **Quiz**. Dynamic binding is used to also handle **Questions**, which are a form of **AuthoredText**, only an answer is expected from the user upon displaying of the **AuthoredText**. **QuizVideo** will use a *key* system to retrieve a **Question** from a **Thread**, this will happen at a predetermined play time from within the video.

### **ThreadNode**
---
##### Members
- **AuthoredText**
- **ThreadNode** *next*


### **Channel** : *Array of Linear Linked Lists*
---
##### Members
- Array of **Playlists**
- Size of the array
- Current total existing **Playlists** in the array

The channel will manage all media related to an online course. Each index of the array will represent a new *topic* in the course. The author will determine the number of topics for their course, and insert media into any of the playlists that coorespond to a topic. Students will access the channel to go through the array of playlists in a linear fashion.

### **Playlist** : *Linear Linked List of Media*
---
##### Members
- Title of the Playlist
- Size of the playlist
- **PlaylistNode** *head*
- **PlaylistNode** *tail*

A playlist manages all media that is related to a particular topic in a course. The author can public media to a **Channel**, which manages an array of **Playlists**. The title of the playlist should be treated as the topic title. The author will be able to publish new media anywhere within the playlist, whether it be the front, end, or middle by index. A **Course** will also contain a *draft* **Playlist**, where the author can build a catalog of media before publishing to their students.

### PlaylistNode
---
##### Members
- **Media** *abstract super* pointer : *for dynamic binding*
- **PlaylistNode** *next*
# What was the problem you were solving in the projects for this course?

The objective of the program was to load data from a file into our chosen data structure, then print out the courses in alphanumeric order, and to print out information of a specific course chosen by the user. The data was read from a file and each line would include a course ID, course name, and zero or many prerequisites for each course. The reason for printing the courses in alphanumeric order was to provide the user with a sorted view that could be used as a sample schedule. The underlying focus for this project was choosing the best data structure (vector, hash table, or binary search tree) for this code problem.

# How did you approach the problem? 

I had a general idea of how I wanted to accomplish this project from a code logic standpoint, but as we studied the various data structures throughout the weeks, I began to question my approach. As I learned about the upsides and downsides of each data structure, choosing what I felt would be the best data structure became more and more complex. There is so much to consider when making this decision and the more I learned the more questions I had. What really helped make the picture clearer to me was when we had to make a runtime analysis of our pseudocode using each data structure. This exercise made me consider factors such as how often the data is accessed, how much memory each data structure uses, and how often data will be inserted or removed from the structure. These factors were important as they directly impact the efficiency and performance of the program.

# How did you overcome any roadblocks you encountered while going through the activities or project?

There were quite a few roadblocks I encountered throughout this course. For instance, understanding the trade-offs between different data structures and how to compare different data structures was a big challenge. There was so much information to consider that it felt overwhelming. However, by conducting a thorough runtime analysis and considering the specific needs of the project, I was able to overcome this challenge. This has been the most challenging course by far, but also the most fascinating! I suspect that a lot of the uncertainty I still feel about choosing the correct data structure will lessen in time by gaining more experience, taking on bigger projects, and by continuing to challenge myself as I continue progressing through my degree.

# How has your work on this project expanded your approach to designing software and developing programs?

This project has significantly expanded my approach to software design and development. I learned new strategies for improving the efficiency of my programs, such as conducting a runtime analysis and considering how the data will be accessed and used in a more detailed manner. These techniques will be invaluable in future projects and I look forward to applying them.

# How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

In this project, I made a conscious effort to write code that is modular, readable, and maintainable. For example, I initially wrote the read, parse, and validation of the prerequisites as one function within my CourseManager. However, I realized that this function was too large and cluttered, so I broke it up into more specialized functions. This made the code easier to read and manage. I’ve learned how important it is to make my code easy to understand, modular, and encapsulated. This project was no exception and I really enjoyed implementing a self-balancing (AVL) tree for the first time.

# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Alex Gao

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: 71.5% accuracy??

Place [x] for what applies.


## UML Diagram



## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > The model analyzes a training dataset of labeled tweets, calculating sentiment scores (-1 to +1) for individual words based on their frequency in positive versus negative posts. It segments new tweets into words for classification, retrieves each word's pre-computed sentiment score, and calculates their arithmetic mean. Tweets with mean scores ≥ 0 are classified as positive, while those < 0 are labeled negative. The algorithm's effectiveness relies on this word-level sentiment aggregation, though it necessarily ignores context and word order.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > Your answer

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > Your answer

4. What accuracy did your algorithm achieve on the provides training and test data? 

   > My accuracy: xx%

   The TA will run your code on Linux and that accuracy value will be used to determine your grade.

5. What were the changes that you made that improved the accuracy the most?
   
   > Your answer

6. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > Your answer

6. What was the most challenging part of the assignment?

   > Your answer

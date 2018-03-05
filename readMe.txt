Sawaiba Sial
0990358

PERSONAL ASSISTANT/ CHATBOT

Description:
Before applications like Siri and Alexa, we had Eliza an early AI and natural language processing tool. This program is similar in concept to Eliza, it implements a Binary Search ADT to provide basic communication to directly asked questions from the user. A sample input file contains a list of keywords and short responses to initiate a conversation. Each keyword and response pair is associated with a rule that provides information about the user rating, system rating, learning rate and a count of the total number of times the rule is used. The conversation starts when the user asks a question. The chatbot separates single words from the text and considers its importance by searching for each one in the binary tree. The response with the highest importance rate is displayed. The program learns by asking the user follow up questions after each response to determine if the feedback was helpful and updates the rule ratings accordingly.

Once the conversation data is read and loaded into the Binary Search Tree the user will be presented with a menu system. The menu system supports the following options:
	Add a new rule - 
	Remove a rule
	Display rules
	Modify rule rating
	Discuss
	Quit



Limitations: SEARCHING IS CASE SENSITIVE

To run the discuss.c enter the following commands:
    make main
    cd bin
    ./runMe rules.txt

To run the test.c enter the following commands:
    make test
    cd bin
    ./runMe
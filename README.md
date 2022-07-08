# DDoS Attack Identifier

During this 15 week course, we dedicated ourselves to learning various data structures and how to implement their methods in order to solve the courses's challenge. After the learning phase, we implemented this knowledge on a database which simulated the behaviour of an internal office network. Finally we used the our results from implementing diferent datastructures to analyse the behaviour of the network and come to conclusions about irregular activity happenening within it.

## Stages
***
During this 15 week period we progresively learned while implementing diferent datastructures and algorithms which unlocked new ablities to explore the database which contained about 20,000 elements.

* [Basic Concepts (Phase 1)](https://github.com/tomasdiazservin1/DDoS-Attack-Identifier-BotNet-/blob/main/retoAvance.cpp): During Phase 1 we gained the ability to read a .csv file and save each line of data in respective verctor variables.
* [Linear Structures (Phase 2)](https://github.com/tomasdiazservin1/DDoS-Attack-Identifier-BotNet-/blob/main/RetoAvance2.cpp): During Phase 2 we were able to save arriving/departing connections from each computer of the internal network and save them inside of a list/stack.
* [Hashing (Phase 3)](https://github.com/tomasdiazservin1/DDoS-Attack-Identifier-BotNet-/blob/main/RetoAvance3.cpp): During Phase 3 we used dictionaries and sets to order arriving/departing connections by IP. At this point we also noticed the abnormal domain 916t95wtls6d3sie7ew6.net and took into account the the computer with username kathleen.reto.com.
* [BST (Phase 4)](https://github.com/tomasdiazservin1/DDoS-Attack-Identifier-BotNet-/blob/main/RetoAvance4.cpp): During Phase 4 we used Binary Search Trees (BST) to find the top 5 departing conections from the internal network and took into account the domain craigslist.com.
* [Graphs (Phase 5)](https://github.com/tomasdiazservin1/DDoS-Attack-Identifier-BotNet-/blob/main/RetoAvance5.cpp): During Phase 5 we used graphs to analyze connections between computers that are a part of the internal network.


## Results
***
After the results given by our development, we were able to determine the following: 
* 916t95wtls6d3sie7ew6.net was the domain where the infection was downloaded which then served as the botmaster and the command control server.
* The first computer infected was kathleen.reto.com with IP address 172..31.90.47 and was also used as a server.
* All 31 computers in the office connect to the computer which was first infected (kathleen.reto.com).
* Our conclusion is that the attack to this network is actually a recollection of users to then use in a DDOS attack to the site craigslist.com. This can be clearly seen on the 19th of August where, for the first and only time registred in the database, craigslist.com appears in the top 5 conections per day. This gives us the impresion that the attacker wanted to overwhelm craigslist's server using this network's computers found using a ping sweep which were then controled by the insturctions distributed by the attacker's server to the first computer infected (kathleen.reto.com).

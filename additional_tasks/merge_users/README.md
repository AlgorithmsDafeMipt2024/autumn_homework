# Users merge

There are n users, each of them corresponds to a list of emails (total m emails). For example:
user1 -> xxx@ya.ru, foo@gmail.com, lol@mail.ru  
user2 -> foo@gmail.com, ups@pisem.net  
user3 -> xyz@pisem.net, vasya@pupkin.com  
user4 -> ups@pisem.net, aaa@bbb.ru  
user5 -> xyz@pisem.net

It is assumed that if two users have a common email, then they are the same user.

We need to build and implement an algorithm that merges users. The output should be a list of users with their email addresses (the same as the input).

In the above example, the answer to the task would be as follows:
user1 -> xxx@ya.ru, foo@gmail.com, lol@mail.ru, ups@pisem.net, aaa@bbb.ru  
user3 -> xyz@pisem.net, vasya@pupkin.com


Translated with DeepL.com (free version)
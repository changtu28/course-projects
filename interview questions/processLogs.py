# Question 

# 2. Suspicious Activity From Logs Application logs are useful in analyzing interaction with an 
# application and may also be used to detect suspicious activities. A log file is provided as a 
# string array where each entry represents a money transfer in the form "sender_user_id 
# recipient_user_id amount. Each of the values is separated by a space. sender_user_id and 
# recipient_user_id both consist only of digits, are at most 9 digits long and start with non-zero 
# digit amount consists only of digits, is at most 9 digits long and starts with non-zero digit Logs 
# are given in no particular order. Write a function that returns an array of strings denoting user_id's 
# of suspicious users who were involved in at least threshold number of log entries. The id's should be
#  ordered ascending by numeric value Example logs = ["88 99 200", "88 99 300, "99 32 100", 12 12 153
#  threshold = 2 The transactions count for each user, regardless of role are: Transactions 12 There are 
#  two users with at least threshold = 2 transactions: 99 and 88. In ascending order, the return array is 
#  [88! "991 Note: In the last log entry, user 12 was on both sides of the transaction. This counts as 
#  only 1 transaction for user 12. Function Description Complete the function processLogs in the editor 
#  below. The function has the following parameter(s): string logsin): each logsi denotes theith entry in
#   the logs int threshold the minimum number of transactions that a user must have to be included in the 
#   result Returns string]: an array of user id's as strings, sorted ascending by numeric value Constraints 
#   • 1sns 10 • 1 s threshold sn • The sender_user_id, recipient_user_id and amount contain only characters 
#   in the range ascii['0'-'9'). • The sender_user_id, recipient_user_id and amount start with a non-zero 
# digit. • 0 < length of sender_user_id, recipient_user_id, amount s 9. • The result will contain at least
#  one element. Input Format Format for Custom Testing Input from stdin will be processed as follows and 
#  passed to the function. The first line contains the integer, n, the size of logs. The following n lines 
#  contain a string, logs/U. The last line contains an integer, threshold. Sample Case 0 Sample Input STDIN 
#  Function logs [] size n = 4 1 2 50 - logs = ["1.2 50", "1 7 70","13 20", "2 2 17"] 1 7 70 1 3 20 2 2 17 
#  ? threshold = 2 Sample Output Explanation ID Transactions 1 wN Only users 1 and 2 have at least threshold
#   2 transactions. The return array in numerically ascending order is "2"). Note that in the last log entry,
# the user with id 2 performed both roles in the transaction. This is counted as one transaction for the user.
# V Sample Case 1 Sample Input STDIN Function 4 ? logs [] size n = 4 9 7 50 ? logs = ["9 7 50","22 7 20", 
# "33 7 50", "22 7 30"] 227 20 33 7 50 22 7 30 ? threshold = 3 

# n=["88 99 200","88 99 300","99 32 100","12 12 15"]
# n=['1 2 50','1 7 70', '1 3 20','2 2 17'] 2
# n=['9 7 50','22 7 20','33 7 50','22 7 30'] 3
def processLogs(n,threshold):
    n=list(map(lambda x: [int(i) for i in x], map(str.split, n)))
    ret=[]
    for i in range(0,len(n)):
       for j in range(0,3):
           sum=0
           temp=n[i][j]
           for k in range(0,len(n)):
               for l in range(0,3):
                   if(n[k][l]==temp):
                       sum=sum+1
                       break
           if(sum>=threshold):
               if temp not in ret:
                   ret.append(temp)
    return (ret)

n_=["88 99 200","88 99 300","99 32 100","12 12 15"]   
threshold_=2
print(processLogs(n_,threshold_))  

n_=['1 2 50','1 7 70', '1 3 20','2 2 17']  
threshold_=2
print(processLogs(n_,threshold_))  

n_=['9 7 50','22 7 20','33 7 50','22 7 30'] 
threshold_=3
print(processLogs(n_,threshold_))  










    
    
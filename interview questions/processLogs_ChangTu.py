'''

        Suspicious Activity From Logs


        Author: Chang Tu


'''


def processLogs(n, threshold):

    # make a transaction list that takes only sender and reciever

    transaction_list = []

    # make a transaction dictionary for counts

    transactions = {}
    for i in n:
        sender = i.split()[0]
        receiver = i.split()[1]

        # Avoid dulplicates counts while the sender is the receiver

        if sender == receiver:
            transaction_list.append([sender])
        else:
            transaction_list.append([sender, receiver])

    # print('transaction_list',transaction_list)

    for transaction in transaction_list:

        # print('transaction',transaction)

        for user in transaction:
            if user in transaction:
                if user not in transactions:  # check if user exists in the dictionary
                    transactions[user] = 1
                else:
                    transactions[user] = transactions.get(user) + 1

    # Stores the thresholds

    threshold_list = []
    for (key, value) in transactions.items():
        if value >= threshold:
            threshold_list.append(key)

    # sort the threshold list in acending order and print it out

    for thresh in sorted(threshold_list):
        print(thresh)


    # explaination
    # print(transaction_list)
    # print(transactions)
    # print(sorted(threshold_list))
    # print((threshold_list))

n_ = ['99 32 100', '88 99 200', '88 99 300', '12 12 15']
threshold_ = 2
processLogs(n_, threshold_)

n_ = ['1 2 50', '1 7 70', '1 3 20', '2 2 17']
threshold_ = 2
processLogs(n_, threshold_)

n_ = ['9 7 50', '22 7 20', '33 7 50', '22 7 30']
threshold_ = 3
processLogs(n_, threshold_)

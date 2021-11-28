
/*

        Suspicious Activity From Logs

        Author: Chang Tu


*/

function processLogs(n, threshold) {
    let transaction_list = [];
    var transactions = {};
    for (i in n) {
        // console.log(n[i]);
        let sender = n[i].split(' ')[0];
        // console.log(n[i].split(' ')[0]);
        // console.log(n[i].split(' '));
        let receiver = n[i].split(' ')[1];
        // console.log(sender);
        if (sender == receiver) {
            transaction_list.push([sender]);
        } else {
            transaction_list.push([sender, receiver]);
        }

    }
    for (transaction in transaction_list) {
        let transac = transaction_list[transaction];
        // let transaction_=transaction_list[transaction];
        for (user in transac) {
            if (user in transac) {
                let userid = transaction_list[transaction][user];
                // console.log(transaction_list[transaction]);
                if (!(userid in transactions)) {
                    transactions[userid] = 1;
                    //transactions[user]=1;
                } else {
                    transactions[userid] = transactions[userid] + 1;

                }
            }

        }
    }
    // Stores the thresholds     
    let threshold_list = [];
    for (key in transactions) {
        key_index = Object.keys(transactions).indexOf(key.toString());
        let current_value = (Object.values(transactions)[key_index]);
        if (current_value >= threshold) {
            threshold_list.push(key)
        }
        // console.log(a);

        // console.log(Object.keys(transactions).indexOf(a.toString()));
    }


    for (thresh in threshold_list.sort()) {
        console.log(threshold_list.sort()[thresh]);

    }


    // console.log(transaction_list);
    // console.log(transactions);
    // console.log(threshold_list);

}


let n_ = ["99 32 100", "88 99 200", "88 99 300", "12 12 15"];
let threshold_ = 2;
(processLogs(n_, threshold_));



let n2 = ['1 2 50', '1 7 70', '1 3 20', '2 2 17'];
let threshold1 = 2;
(processLogs(n2, threshold1));



let n3 = ['9 7 50', '22 7 20', '33 7 50', '22 7 30'];
let threshold2 = 3;
(processLogs(n3, threshold2));
What is a Bitcoin really? It is just a unit of account. Just like grams is a unit of mass, gallon is a unit of volume, dollars are a unit of money.
Just like a dollar bill
1) Can be possessed
2) can be spent or transferred
3) is extremely hard to copy

Similarly, bitcoin
1) can be possessed
2) can be spent or transferred
3) impossible to copy

So it can be used as an alternative for distribution of wealth.

How are bitcoins tracked and distributed
----------------------------------------
There is no central server which stores all the bitcoin transactions that have happened till now. Infact thousands of servers exist in the world which keep track of all the bitcoins transactions and how much bitcoins are owned by whom. These servers are called "a full node". Anyone in the world can setup and run a full node. Each node has the full public ledger - i.e a record of every bitcoin transaction that ever happened, in history, all the way to back to the very beginning of bitcoin. As of June 2021, the size of the bitcoin ledger is approx 343 GB.

Now to use bitcoins you need some kind of a device which functions like a wallet. It could be an app running on your computer, a mobile app, a service offerred by a website or something else entirely. Your wallet can inform any "ONE FULL NODE" a bitcoin transaction. That full node will relay the transaction to other nodes, which will relay it to other nodes, and so on - similar to how BitTorrent works. It only takes about 7 seconds for a transaction to propogate across the entire Bitcoin network.

What is a transaction
---------------------
When you initiate a transaction, you are really not sending anything to the other party. Instead all that is happening, is that the wallet re-assigns those bitcoins, from one owner to another, by adding a transaction to the public ledger. See the image public-ledge.png. it shows you three transactions.
Every transaction has a set of Inputs and Outputs. Input identies which Bitcoin is being spent. and the Output identifies the new owners of the bitcoin.
"Each Input is just a digitally signed reference to some output from a previous transaction." This is the most important statement. We will come back to it again later after reading and understanding a few more things. Once an output is spent by a subsequent input, no other transaction can spend that output again. That's what makes bitcoins impossible to copy.

Each unspent output represents some amount of bitcoin that is currently in someone’s possession. If you add up all unspent outputs on the public ledger, you’ll get the same total amount as there are bitcoins in existence. You could even go so far as to say that the unspent outputs are the bitcoins.

Note that nobody’s real name appears anywhere within a transaction. That’s why Bitcoin is often said to be pseudonymous. Instead of real names, bitcoins are assigned to addresses such as 1PreshX6QrHmsWbSs8pHpz6kLRcj9kdPy6. A Bitcoin address is like a numbered bank account, only much easier to create, and each person can have a potentially unlimited number of them. the Output in a bitcoin transaction is actually an address.

Where Do Addresses Come From?
------------------------------
Obviously, if you want to receive bitcoins, you need to have a Bitcoin address. Your wallet can generate addresses for you.

In order to generate an address, your wallet first generates a private key. A private key is nothing but a large number roughly between 1 and 2^256. To make such numbers shorter to write, it’s customary to encode them as sequence of numbers and letters.

Next, your wallet converts that private key to a Bitcoin address using a well-known function. This function is very straightforward for a computer to perform. If anyone knows your private key, they could easily convert it to a Bitcoin address, too. In fact, many Bitcoin wallets have a feature allowing you to import private keys.

On the other hand, it’s extremely difficult to go the other way. If someone knows only your Bitcoin address, it’s virtually impossible to figure out what the private key was.

It’s perfectly safe to give your Bitcoin addresses to other people, but extremely important to keep your private keys secret. Most of the time, as a Bitcoin user, you’ll never even see your own private keys. Typically, your wallet keeps track of your private keys for you, usually by storing them in an encrypted wallet file, either on your hard drive, on a server on the Internet, or elsewhere.

How Are Transactions Authorized?
-------------------------------


/** This means that an Input to a transaction is the identity of a bitcoin, but how is that identity created. It is created using the Output of the previous transaction by digitally signing it. This means that the owner of a bitcoin will digitally sign the bitcoin it owns using its private
**/

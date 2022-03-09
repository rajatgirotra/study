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

Now to use bitcoins you need some kind of a device which functions like a wallet. It could be an app running on your computer, a mobile app, a service offerred by a website or something else entirely. Your wallet can inform any "ONE FULL NODE" of a bitcoin transaction. That full node will relay the transaction to other nodes, which will relay it to other nodes, and so on - similar to how BitTorrent works. It only takes about 7 seconds for a transaction to propogate across the entire Bitcoin network.

What is a transaction
---------------------
When you initiate a transaction, you are really not sending anything to the other party. Instead all that is happening, is that the wallet re-assigns those bitcoins, from one owner to another, by adding a transaction to the public ledger. See the image public-ledge.png. it shows you three transactions.
Every transaction has a set of Inputs and Outputs. Input identies which Bitcoin is being spent. and the Output identifies the new owners of the bitcoin.
"Each Input is just a digitally signed reference to some output from a previous transaction." This is the most important statement. We will come back to it again later after reading and understanding a few more things. Once an output is spent by a subsequent input, no other transaction can spend that output again. That's what makes bitcoins impossible to copy.

Each unspent output represents some amount of bitcoin that is currently in someone’s possession. If you add up all unspent outputs on the public ledger, you’ll get the same total amount as there are bitcoins in existence. You could even go so far as to say that the unspent outputs are the bitcoins.

Note that nobody’s real name appears anywhere within a transaction. That’s why Bitcoin is often said to be pseudonymous. Instead of real names, bitcoins are assigned to addresses such as 1PreshX6QrHmsWbSs8pHpz6kLRcj9kdPy6. A Bitcoin address (also some people refer to it as a wallet address) is like a numbered bank account, only much easier to create, and each person can have a potentially unlimited number of them. the Output in a bitcoin transaction is actually an address.

Where Do Addresses Come From?
------------------------------
Obviously, if you want to receive bitcoins, you need to have a Bitcoin address. Your wallet can generate addresses for you.

In order to generate an address, your wallet first generates a private key. A private key is nothing but a large number roughly between 1 and 2^256. To make such numbers shorter to write, it’s customary to encode them as sequence of numbers and letters.

Next, your wallet converts that private key to a Bitcoin address using a well-known function (see 2_BitcoinAddressGenerator.py). This function is very straightforward for a computer to perform. If anyone knows your private key, they could easily convert it to a Bitcoin address, too. In fact, many Bitcoin wallets have a feature allowing you to import private keys.

On the other hand, it’s extremely difficult to go the other way. If someone knows only your Bitcoin address, it’s virtually impossible to figure out what the private key was.

It’s perfectly safe to give your Bitcoin addresses to other people, but extremely important to keep your private keys secret. Most of the time, as a Bitcoin user, you’ll never even see your own private keys. Typically, your wallet keeps track of your private keys for you, usually by storing them in an encrypted wallet file, either on your hard drive, on a server on the Internet, or elsewhere.

How Are Transactions Authorized?
-------------------------------
The first question?? Who should authorize a transaction to be added to the ledger. Offcourse it should be the one initiating the transfer. i.e. the sender. But how does he do that?

For authorization we need to guarantee two things.
1) The initiater of the transaction is really a person who owns the bitcoins being transferred.
2) He has really authorized it.

And there is a 3rd very important problem
Double Spending??
=================
i.e. how do you guarantee that the owner of a bitcoin doesnt spend a coin more than once.
The proposed solution to the double-spending problem is to use a peer-to-peer (i.e decentralized) network.
The network will timestamp transactions by hashing them into an ongoing chain of hash-based proof-of-work, forming a record that cannot be changed without redoing the proof-of-work. The longest chain not only serves as proof of the sequence of events witnessed, but proof that it came from the largest pool of CPU power. As long as a majority of CPU power is controlled by nodes that are not cooperating to
attack the network, they'll generate the longest chain and outpace attackers.

To see how this 1) and 2) is taken care of, take a closer look at the second transaction public-ledger.png, b6f4ec453a021ac561…. This transaction spends the bitcoins from previous output e14768c1d648b98a52…:0. When we examine that previous output, we see that those bitcoins were previously sent to the address 1NqUaJrFeStshjad1bhrEFFzWSQw6JHbqv. Which means that bitcoin address 1NqUaJrFeStshjad1bhrEFFzWSQw6JHbqv is the current owner.

Now the current owner must use his private key to generate a digital signature. By what does is he really signing?? He is signing the previous output e14768c1d648b98a52…:0. 

In Bitcoin, a valid digital signature serves as proof that the transaction was authorized by the address’s owner. Here’s what makes it safe: Just as a private key was required to generate that address, the same private key is required, once again, to generate a valid digital signature.

So if we have a valid digital signature, it means that both points above are ticked.
A digital signature is only valid if a specific equation (ECDSA Signature verification algorithm on Wikipedia) is satisfied by
1) the bitcoin address,
2) the previous output (i.e. the data that is signed)
3) and the digital signature.
As you’d expect, every time a Bitcoin node receives a new transaction, it checks to make sure each digital signature is valid. The node has no idea which private key was used to generate each signature, but that’s OK, because it doesn’t need to know. It only needs to verify that the equation is satisfied.


Bitcoin Wallets
===============

Some Wallet Types
There’s already a wide range of Bitcoin wallets to choose from, but in most cases, the purposes of the wallet are the same:

To store your private keys.
To send bitcoins to other people.
To generate addresses, so you can receive bitcoins from other people.
To view your transaction history and current balance.

A desktop wallet is an application you install on Windows, MacOS or Linux. Examples include
1) Electrum,
2) Multibit
3) and Bitcoin QT.
Your private keys are stored locally, in a file somewhere on your hard drive such as wallet.dat, and the security of your bitcoins is only as good as your ability to protect that file from data loss and theft. Exceptionally, Bitcoin QT also turns your computer into a Bitcoin node, and therefore requires much more disk space and bandwidth than the other applications.

There are also web wallets such as
1) Coinbase
2) or Blockchain.info’s My Wallet service.
When using a web wallet, your private keys are stored – usually encrypted – on the website’s servers instead of your own hard drive. Some web wallets are also Bitcoin exchanges, such as 
a) Bitstamp or
b) Virtex,
where bitcoins can be traded for US dollars and other currencies.

A mobile wallet is an app you install on a smartphone or tablet. Many mobile wallets, such as the Coinbase app, are simply interfaces to a web wallet, which means that your private keys are once again stored online. One notable exception is Bitcoin Wallet for Android, which stores private keys directly on your mobile device.

Since virtually all smartphones have a built-in camera, QR codes have become a popular way to communicate Bitcoin addresses. You can send bitcoins to someone by scanning their QR code with your mobile wallet.

Bitcoin’s protocol is completely open, allowing anyone to implement an application or device that is compatible with Bitcoin. In effect, the entire Bitcoin ecosystem has been crowdsourced. This has sparked all sorts of innovation – there are many more Bitcoin wallet and point-of-sale devices than the ones I’ve mentioned here, and there are certainly more to come. The landscape is changing constantly.

Unfortunately, this openness also creates an opportunity for scammers. That’s why you must choose your wallet carefully. Do some research before deciding that your wallet provider is trustworthy. In the case of a web wallet, you must trust that website with your bitcoins exactly as you would trust a bank with your cash.

Value of Bitcoins
================
If you’re looking for something of value behind Bitcoin, I’d argue that it’s the private keys. Certainly, every fraction of a bitcoin is backed by one. And once bitcoins are sent to an address, the corresponding private key becomes extremely valuable.

Consider the Bitcoin address 1933phfhK3ZgFQNLGSDXvqCn32k2buXY8a. It currently contains 111114 bitcoins. At the time of writing, that’s worth about $90 million US. If you only knew the private key for that address, you could spend that $90 million as if it were yours.

Suffice to say, thieves around the world are itching to discover people’s private keys. A new breed of wallet-stealing malware has already emerged. Safeguarding your wallet is very very important.

So, when you buy bitcoins… what it is that you own, exactly?
============================================================

When you own bitcoins, what you have is the exclusive ability to add specific transactions to the public ledger. Your bitcoins exist as unspent outputs from previous transactions on the ledger, sent to an address that your wallet created out of thin air, waiting for you to use as inputs in a future transaction. Your wallet is the only wallet that can digitally sign those inputs, because it contains a private key that no one else has.

So a cryptocurrency is a digital asset which allows you to exchange VALUE between two parties.

Further Information
===================
Now that you know exactly what a bitcoin is, how it’s secured, and how it’s transferred, you have a foundation for understanding further information about Bitcoin.

Bitcoin’s public ledger is also known as the blockchain. Since the blockchain is totally public, people have built websites to interactively browse its contents, such as
1) Blockchain.info
2) and BlockExplorer.
3) BTC.com

So What is a blockchain
=======================
This technology to keep all the transactions (i.e. the ledger) that ever happened in bitcoin de-centralized is called the blockchain.
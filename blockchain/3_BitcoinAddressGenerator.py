import hashlib,base58,binascii,ecdsa, codecs

# Step1: Generate ECDSA Private Key")
ecdsaPrivateKey = ecdsa.SigningKey.generate(curve=ecdsa.SECP256k1)
print("ECDSA Private Key: ", ecdsaPrivateKey.to_string().hex())
print("------------------------------------------------------")
# Step2: Generate ECDSA Public Key from value at Step#1
ecdsaPublicKey = '04' +  ecdsaPrivateKey.get_verifying_key().to_string().hex()
print("ECDSA Public Key: ", ecdsaPublicKey)
print("------------------------------------------------------")
# Step3: SHA256(value at Step#2)
hash256FromECDSAPublicKey = hashlib.sha256(binascii.unhexlify(ecdsaPublicKey)).hexdigest()
print("SHA256(ECDSA Public Key): ", hash256FromECDSAPublicKey)
print("------------------------------------------------------")
# Step4: RIDEMP160(value at Step#3)
ridemp160FromHash256 = hashlib.new('ripemd160', binascii.unhexlify(hash256FromECDSAPublicKey))
print("RIDEMP160(SHA256(ECDSA Public Key)): ", ridemp160FromHash256.hexdigest())
print("------------------------------------------------------")
# Step5: Prepend 00 as network byte to value at Step#4, This is actually a version byte for bitcoin mainnet. 
# BTC has a testnet where developers can test and experiment, without having to use real BTC or owrrying about breaking the main bitcoin chain
prependNetworkByte = '00' + ridemp160FromHash256.hexdigest()
print("Prepend Network Byte to RIDEMP160(SHA256(ECDSA Public Key)): ", prependNetworkByte)
print("------------------------------------------------------")
# Step6: Apply SHA256 to value at Step#5 at 2 times to generate Checksum
hash = prependNetworkByte
for x in range(1,3):
    hash = hashlib.sha256(binascii.unhexlify(hash)).hexdigest()
    print("\t|___>SHA256 #", x, " : ", hash)
print("------------------------------------------------------")
# Step7: Get first 4 bytes of value at Step#6 as Checksum
cheksum = hash[:8]
print("Checksum(first 4 bytes): ", cheksum)
print("------------------------------------------------------")
# Step8: Append Checksum to value at Step#5
appendChecksum = prependNetworkByte + cheksum
print("Append Checksum to RIDEMP160(SHA256(ECDSA Public Key)): ", appendChecksum)
print("------------------------------------------------------")
# Step9: Generate Bitcoin Address with apply Base58 Encoding to value at Step#8
bitcoinAddress = base58.b58encode(binascii.unhexlify(appendChecksum))
print("Bitcoin Address: ", bitcoinAddress.decode('utf8'))

# Address
# Bitcoin address is a Base58Check representation of a Hash160 of a public key with a version byte 0x00 which maps to a prefix "1". 1 is most common and denotes a simple "pay-to-PubKey" transaction. This transaction shows an actual recipient address.

# A variant of an address is P2SH address: a hash of a spending script with a version byte 0x05 which maps to a prefix "3" (ex. 3NukJ6fYZJ5Kk8bPjycAnruZkE5Q7UW7i8). 3 indicates a "pay-to-script-hash" address that contains a hash (one way fingerprint) of a script that can be used for multiple things including address obfuscation and multi-signature requirements. This script is required to be a valid bitcoin transaction script, but the full script behind the scenes is not public, just the hash.

# Another variant of an address is not a hash, but a raw private key representation (e.g. 5KQntKuhYWSRXNqp2yhdXzjekYAR7US3MT1715Mbv5CyUKV6hVe). It is rarely used, only for importing/exporting private keys or printing them on paper wallets.


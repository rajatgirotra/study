import datetime as dt
import hashlib
import json
from flask import Flask, jsonify

app = Flask(__name__)


class Blockchain(object):
    def __init__(self):
        self.chain = []
        self.create_block(proof=1, previous_hash='0')

    def get_previous_block(self):
        return self.chain[-1]

    def hash(self, block):
        encoded_data = json.dumps(block, sort_keys=True).encode()
        return hashlib.sha256(encoded_data).hexdigest()

    def proof_of_work(self, previous_proof):
        pow = 1
        while True:
            hash_operation = hashlib.sha256(str(pow**2 - previous_proof**2).encode()).hexdigest()
            if hash_operation[:4] != '0000':
                pow += 1
            else:
                print(f'{hash_operation}')
                break
        return pow

    def create_block(self, proof, previous_hash):
        block = {'index': len(self.chain) + 1,
                 'timestamp': str(dt.datetime.now()),
                 'proof': proof,
                 'previous_hash': previous_hash
                 }
        self.chain.append(block)
        return block

    def is_chain_valid(self, chain):
        block_index = 1
        # assume genesis block is always valid
        while block_index < len(chain):
            previous_block = chain[block_index-1]
            block = chain[block_index]
            print(f'{block_index}')
            previous_hash = self.hash(previous_block)
            if block['previous_hash'] != previous_hash:
                print(f'{block["previous_hash"]}, {previous_hash}')
                return False
            proof = block['proof']
            previous_proof = previous_block['proof']
            hash_operation = hashlib.sha256(str(proof**2 - previous_proof**2).encode()).hexdigest()
            if hash_operation[:4] != '0000':
                return False
            block_index += 1
        return True


blockchain = Blockchain()


@app.route('/mine_block', methods=['GET'])
def mine_block():
    previous_block = blockchain.chain[-1]
    previous_proof = previous_block['proof']
    previous_hash = blockchain.hash(previous_block)
    new_proof = blockchain.proof_of_work(previous_proof)
    new_block = blockchain.create_block(new_proof, previous_hash)
    response = new_block.copy()
    response['message'] = 'Congratulations! You have mined a new block'
    return response, 200


@app.route('/get_chain', methods=['GET'])
def get_chain():
    chain = blockchain.chain
    response = {'chain': chain, 'length': len(chain)}
    return jsonify(response), 200


@app.route('/is_valid', methods=['GET'])
def is_valid():
    chain = blockchain.chain
    valid = blockchain.is_chain_valid(chain)
    if valid:
        response = {'message': 'All blocks in your blockchain are valid!!'}
    else:
        response = {'message': 'NOT ALL blocks in your blockchain are valid!!'}
    return jsonify(response), 200


app.run(host="0.0.0.0", port=5000)

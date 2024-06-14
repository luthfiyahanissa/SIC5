from flask import Flask, request, jsonify

app = Flask('Flask_Test')
datasensor = []

@app.route('/data',methods=['POST'])
def data():
    datasensor.append(request.get_json())
    return "Success"

@app.route('/data', methods= ['GET'])
def push():
    return jsonify(datasensor)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
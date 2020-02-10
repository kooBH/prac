import json

with open("data.json") as json_file:
    json_data = json.load(json_file)
    a = json_data["a"]
    ab=json_data["a"]["ab"]
    print(a)
    print(ab)
    print(ab[0])


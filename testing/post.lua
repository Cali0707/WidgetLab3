wrk.method = "POST"
wrk.body = "{\n\t\"deviceId\": 1250,\n\t\"thermistorValue\": 450,\n\t\"photoResistorValue\": 400}"
wrk.headers["Content-Type"] = "application/json"
wrk.path = "/api/sensors/add-data"

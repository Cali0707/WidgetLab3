void setup() {
  Serial1.begin(9600);
  delay(10000);
  Serial1.write("{\n\t\"deviceId\": 1234,\n\t\"photo\": 200,\n\t\"therm\":1234\n}");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
  Serial1.write("{\n\t\"deviceId\": 1234,\n\t\"photo\": 200,\n\t\"therm\":1234\n}");

}

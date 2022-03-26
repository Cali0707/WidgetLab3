# WidgetLab3
This repository runs a backend webserver and frontend React application to process and 
display information collected from an IoT device.

# Setup
WidgetLab3 has two applications which both reside in this monorepo, along with a nginx 
reverse-proxy instance and a MongoDB database. In terms of directories there are:
- `frontend`: the frontend React application
- `backend`: the backend Express.js application
- `nginx`: config files for the nginx reverse-proxy
In addition to these directories, there is a fourth empty directory which you must create before
running the application to allow MongoDB to persist data between runs. To create this, run the 
following command in the root directory of WidgetLab3:
```shell
mkdir mongo-volume
```
## Environment Setup
To build the application, you need to have a proper `.env` file configured in the root directory 
of this repository. To set this up:
1. Copy `.env.default` to `.env`. This can be done with `cp .env.default .env`.
2. Replace the placeholder values for `MONGODB_USER` and `MONGODB_PASSWORD` with values of your choosing.

In addition to a `.env` file, you will need a `secrets.h` file in your `arduino` directory which will hold the credentials
for your local Internet network. To set this up:
1. Go to the `arduino` directory with `cd arduino`
2. Copy `secrets.default.h` to `secrets.h`. This can be done with `cp secrets.default.h secrets.h`.
3. Fill in the string value for `NETWORK_SSID` with the name of your internet network, `NETWORK_PASSWORD` with the password, and `SERVER` with the url for your server (excluding the `https://`).
## Runtime Setup
To run the application, you need to have Docker installed to run MongoDB and the frontend and
backend applications in containers. To install Docker:

1. Install [docker](https://docs.docker.com/get-docker/)
2. Navigate to the root folder of this repository in your terminal
3. Run `docker-compose up --build`
4. You can now access the backend server at http://localhost:5000, and the frontend at http://localhost. Additionally, the backend can be accessed from `http://localhost/api/`

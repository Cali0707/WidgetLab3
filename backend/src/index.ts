import express, {Request, Response} from 'express';
import bodyParser from "body-parser";
const cors = require("cors");
import mongoose from "mongoose";
import sensorDataRouter from "./routes/sensorDataRouter";
import {resolve} from "path"

if (process.env.NODE_ENV !== 'production') {
    require("dotenv").config({path: resolve(__dirname, "../../.env")})
}

// Initialize Express app
const app = express();

// Get the port for the app to run on
const port = process.env.API_PORT || 5000;

// Add middleware for CORS headers, decoding http requests
app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

// Add router for requests
app.use("/sensors", sensorDataRouter)

// Connect to MongoDB
const {MONGODB_USER, MONGODB_PASSWORD, DB_NAME} = process.env;
// console.log(MONGODB_USER)
const mongoURI = `mongodb://${MONGODB_USER}:${MONGODB_PASSWORD}@${process.env.NODE_ENV === "production" ? "mongo": "localhost"}:27017/?authSource=admin`
// console.log(mongoURI)
mongoose.connect(mongoURI)
    .then(() => app.listen(port, () => {
        console.log(`Backend running on http://localhost:${port}`)
    }))
    .catch(e => {
        throw e;
    })

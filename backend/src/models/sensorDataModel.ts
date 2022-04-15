import {ISensorData} from "../types/sensorDataType";
import {model, Schema} from "mongoose";

const waterDataSchema: Schema = new Schema(
    {
        deviceId: {
            type: Number,
            required: true
        },
        photo: {
            type: Number,
            required: true
        },
        therm: {
            type: Number,
            required: true
        },
        timestamp: {
            type: Date,
            required: true,
            default: () => Date.now()
        },
    },
    {
        timeseries: {
            timeField: 'timestamp',
            metaField: 'sensorId',
            granularity: "seconds"
        }
    }
);

export default model<ISensorData>("WaterData", waterDataSchema);

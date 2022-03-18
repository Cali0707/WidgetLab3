import {ISensorData} from "../types/sensorDataType";
import {model, Schema} from "mongoose";

const waterDataSchema: Schema = new Schema(
    {
        deviceId: {
            type: Number,
            required: true
        },
        photoResistorValue: {
            type: Number,
            required: true
        },
        thermistorValue: {
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

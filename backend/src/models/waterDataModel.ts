import {IWaterData} from "../types/waterDataType";
import {model, Schema} from "mongoose";

const waterDataSchema: Schema = new Schema(
    {
        sensorId: {
            type: Number,
            required: true
        },
        dataType: {
            type: String,
            required: true
        },
        value: {
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

export default model<IWaterData>("WaterData", waterDataSchema);

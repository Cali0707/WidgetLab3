import {Document} from "mongoose";

export interface ISensorData extends Document {
    deviceId: number
    therm: number
    photo: number,
    timestamp?: Date
}

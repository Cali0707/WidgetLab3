import {Document} from "mongoose";

export interface ISensorData extends Document {
    deviceId: number
    thermistorValue: number
    photoResistorValue: number,
    timestamp?: Date
}

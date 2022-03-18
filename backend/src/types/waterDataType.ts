import {Document} from "mongoose";

export interface IWaterData extends Document {
    sensorId: number
    dataType: string,
    value: number,
}

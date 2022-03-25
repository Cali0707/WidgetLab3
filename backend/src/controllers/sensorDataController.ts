import {Request, Response} from "express";
import {ISensorData} from "../types/sensorDataType";
import WaterData from "../models/sensorDataModel";

const addSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        // console.log(req.body)
        const body = req.body as Pick<ISensorData, "deviceId" | "thermistorValue" | "photoResistorValue">
        // console.table([body.deviceId, body.photoResistorValue, body.thermistorValue])

        const sensorData: ISensorData = new WaterData({...body});
        await sensorData.save();
        res.status(200).json({message: "Data saved"});
    } catch (e) {
        throw e;
    }
}

const getSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        const sensorDataPoints: ISensorData[] = await WaterData.find()
        res.status(200).json({ waterDataPoints: sensorDataPoints })
    } catch (e) {
        throw e
    }
}

export {
    addSensorData,
    getSensorData
}

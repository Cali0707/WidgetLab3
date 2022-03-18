import {Request, Response} from "express";
import {ISensorData} from "../types/sensorDataType";
import WaterData from "../models/sensorDataModel";

const addSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        console.log(req.body)
        const body = req.body as Pick<ISensorData, "deviceId" | "thermistorValue" | "photoResistorValue">
        console.table([body.deviceId, body.photoResistorValue, body.thermistorValue])

        const waterData: ISensorData = new WaterData({...body});
        await waterData.save();
        res.status(200).json({message: "Data saved"});
    } catch (e) {
        throw e;
    }
}

const getSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        const waterDataPoints: ISensorData[] = await WaterData.find()
        res.status(200).json({ waterDataPoints })
    } catch (e) {
        throw e
    }
}

export {
    addSensorData,
    getSensorData
}

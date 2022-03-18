import {Request, Response} from "express";
import {IWaterData} from "../types/waterDataType";
import WaterData from "../models/waterDataModel";

const addWaterData = async (req: Request, res: Response): Promise<void> => {
    try {
        const body = req.body as Pick<IWaterData, "sensorId" | "dataType" | "value">

        const waterData: IWaterData = new WaterData({...body});
        await waterData.save();
        res.status(200).json({message: "Data saved"});
    } catch (e) {
        throw e;
    }
}

const getWaterData = async (req: Request, res: Response): Promise<void> => {
    try {
        const waterDataPoints: IWaterData[] = await WaterData.find()
        res.status(200).json({ waterDataPoints })
    } catch (e) {
        throw e
    }
}

export {
    addWaterData,
    getWaterData
}

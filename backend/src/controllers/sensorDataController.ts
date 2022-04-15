import {Request, Response} from "express";
import {ISensorData} from "../types/sensorDataType";
import WaterData from "../models/sensorDataModel";

// Route for posting new sensor data to.
// Data must be structured as: {deviceId: number, thermistorValue: number, photoResistorValue: number}
const addSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        const body = req.body as Pick<ISensorData, "deviceId" | "therm" | "photo">
        const sensorData: ISensorData = new WaterData({...body});
        await sensorData.save();
        res.status(200).json({message: "Data saved"});
    } catch (e) {
        throw e;
    }
}

// Returns array of all sensor data
// TODO: update this to handle pagination in the future
const getSensorData = async (req: Request, res: Response): Promise<void> => {
    try {
        const sensorDataPoints: ISensorData[] = await WaterData.find({}, '-_id timestamp thermistorValue photoResistorValue')
        const data = sensorDataPoints.map(({timestamp, therm, photo}) => {
            return {photoResistorValue: getVoltage(photo), thermistorValue: convertToTemp(therm), timestamp }
        })
        res.status(200).json({ waterDataPoints: data })
    } catch (e) {
        throw e
    }
}

// Converts voltage read to temperature following explanation here: https://learn.adafruit.com/thermistor
const convertToTemp = (analogVolt: number) => {
    const resistance = 10000 / (1023 / (analogVolt - 1));
    let temperature = ((Math.log(resistance / 10000) * (1 / 4000)) + (1 / (25 + 273.15)));
    return (1 / temperature) - 293; // temp - 273.15 to convert to kelvin, then small constant correction factor to fix error
}

// Converts adv value to voltage for photoresistor
// We mainly do this because otherwise the value is too large to see temp fluctuations
const getVoltage = (adc: number) => {
    return adc * (3.3 / 1023)
}

export {
    addSensorData,
    getSensorData
}

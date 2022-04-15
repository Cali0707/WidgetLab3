import {Router, Request, Response} from "express";
import {addSensorData, getSensorData} from "../controllers/sensorDataController";

const router: Router = Router();

const mockGetSensorData = async (req: Request, res: Response) : Promise<void> => {
    setTimeout(() => {res.status(200).json({
        waterDataPoints: [
            {timestamp: (new Date(Date.now() - 20000)).toISOString().slice(11,19), thermistorValue: 23.4, photoResistorValue: 6},
            {timestamp: (new Date(Date.now() - 15000)).toISOString().slice(11,19), thermistorValue: 22.7, photoResistorValue: 5.9},
            {timestamp: (new Date(Date.now() - 10000)).toISOString().slice(11,19), thermistorValue: 22.1, photoResistorValue: 1.2},
            {timestamp: (new Date(Date.now() - 5000)).toISOString().slice(11,19), thermistorValue: 22.0, photoResistorValue: 1.3},
            {timestamp: (new Date(Date.now())).toISOString().slice(11,19), thermistorValue: 22.1, photoResistorValue: 6},
        ]
    })}, 60)
}

router.get("/data", process.env.MODE === "mock" ? mockGetSensorData :getSensorData);
router.post("/add-data", addSensorData);

export default router;

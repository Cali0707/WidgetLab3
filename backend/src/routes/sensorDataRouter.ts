import {Router} from "express";
import {addSensorData, getSensorData} from "../controllers/sensorDataController";

const router: Router = Router()

router.get("/data", getSensorData);
router.post("/add-data", addSensorData);

export default router;

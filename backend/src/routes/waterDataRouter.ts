import {Router} from "express";
import {addWaterData, getWaterData} from "../controllers/waterDataController";

const router: Router = Router()

router.get("/water-data", getWaterData);
router.post("/add-water-data", addWaterData);

export default router;

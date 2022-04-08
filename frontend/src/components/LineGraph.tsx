import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend, ReferenceLine} from "recharts";
import {useEffect, useState} from "react";

interface TimeSeriesData {
    timestamp: Date,
    photoResistorValue: number,
    thermistorValue: number
}

interface LineGraphProps {
    data: TimeSeriesData[]
}

const LineGraph = ({data}: LineGraphProps) => {
    const [calculatedMargin, setCalculatedMargin] = useState(window.innerWidth * 0.1);

    const handleResize = (e: Event) => {
        setCalculatedMargin(window.innerWidth * 0.1);
    }

    useEffect(() => {
        window.addEventListener("resize", handleResize);
    }, []);

    return (
        <ResponsiveContainer width={"80%"} height={250}>
            <LineChart
                height={200}
                data={data}
                margin={{top: 0, right: 0, left: calculatedMargin, bottom: 0}}
            >
                <CartesianGrid strokeDasharray={"1 1"}/>
                <XAxis dataKey={"timestamp"} />
                <YAxis />
                <Tooltip />
                <Legend />
                <Line type={"monotone"} dataKey={"thermistorValue"} stroke="#8884d8" name="Temperature"/>
                <Line type={"monotone"} dataKey={"photoResistorValue"} stroke={"#82ca9d"} name={"Photo Resistor Voltage"}/>
                <ReferenceLine y={20} label="Threshold Temperature" stroke="#9d9ad9" strokeDasharray="3 3" />
                <ReferenceLine y={7} label="Threshold Turbidity" stroke="#a4deba" strokeDasharray="3 3" />
            </LineChart>
        </ResponsiveContainer>
    )
}

export type { TimeSeriesData };
export default LineGraph;

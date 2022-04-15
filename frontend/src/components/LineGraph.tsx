import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend, ReferenceLine} from "recharts";
import {useEffect, useState} from "react";
import "./LineGraph.css";

interface TimeSeriesData {
    timestamp: Date,
    photoResistorValue: number,
    thermistorValue: number
}

interface LineGraphProps {
    data: TimeSeriesData[],
    label: string,
    dataKey: string,
    threshold: number
}

const LineGraph = ({data, label, dataKey, threshold}: LineGraphProps) => {
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
                style={{fill: "#ffffff"}}
            >
                <CartesianGrid strokeDasharray={"1 1"} style={{fill: "#ffffff"}}/>
                <XAxis dataKey={"timestamp"} style={{fill: "#ffffff"}}/>
                <YAxis style={{fill: "#ffffff"}}/>
                <Tooltip />
                <Legend style={{fill: "#ffffff"}} />
                <Line type={"monotone"} dataKey={dataKey} stroke="#dfb171" name={label}/>
                {/*<Line type={"monotone"} dataKey={"photoResistorValue"} stroke={"#82ca9d"} name={"Photo Resistor Voltage"}/>*/}
                <ReferenceLine y={threshold} label={`Threshold ${label}`} stroke="#c9705c" strokeDasharray="5 5" />
                {/*<ReferenceLine y={7} label="Threshold Turbidity" stroke="#a4deba" strokeDasharray="3 3" />*/}
            </LineChart>
        </ResponsiveContainer>
    )
}

export type { TimeSeriesData };
export default LineGraph;

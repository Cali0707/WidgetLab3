import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend} from "recharts";

interface TimeSeriesData {
    timestamp: Date,
    photoResistorValue: number,
    thermistorValue: number
}

interface LineGraphProps {
    data: TimeSeriesData[]
}

const LineGraph = ({data}: LineGraphProps) => {
    return (
        <ResponsiveContainer width={"80%"} height={250}>
            <LineChart height={200} data={data}>
                <CartesianGrid strokeDasharray={"3 3"}/>
                <XAxis dataKey={"timestamp"} />
                <YAxis />
                <Tooltip />
                <Legend />
                <Line type={"monotone"} dataKey={"thermistorValue"} stroke="#8884d8" name="Temperature"/>
                <Line type={"monotone"} dataKey={"photoResistorValue"} stroke={"#82ca9d"} name={"Photo Resistor Voltage"}/>
            </LineChart>
        </ResponsiveContainer>
    )
}

export type { TimeSeriesData };
export default LineGraph;

import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend, ReferenceLine} from "recharts";

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
                <ReferenceLine y={20} label="Threshold Temperature" stroke="#9d9ad9" strokeDasharray="3 3" />
                <ReferenceLine y={30} label="Threshold Turbidity" stroke="a4deba" strokeDasharray="3 3" />
            </LineChart>
        </ResponsiveContainer>
    )
}

export type { TimeSeriesData };
export default LineGraph;

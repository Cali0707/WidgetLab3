import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend} from "recharts";

interface TimeSeriesData {
    timestamp: Date,
    type: string,
    value: number
}

interface LineGraphProps {
    data: TimeSeriesData[]
    types: string[]
}

const LineGraph = ({data, types}: LineGraphProps) => {
    // Filter total data set to specific type to display
    const filteredData = data.filter(d => types.includes(d.type));
    // Make line for each type provided
    const lines = types.map(t => <Line type={"monotone"} dataKey={t} />)

    return (
        <ResponsiveContainer width={"80%"}>
            <LineChart data={filteredData}>
                <CartesianGrid strokeDasharray={"3 3"}/>
                <XAxis dataKey={"timestamp"} />
                <YAxis />
                <Tooltip />
                <Legend />
                {lines}
            </LineChart>
        </ResponsiveContainer>
    )
}

export default LineGraph;

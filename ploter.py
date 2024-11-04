import pandas as pd
import plotly.graph_objects as go

# Load CSV data
data = pd.read_csv('scheduler_data.csv')

# Create traces for each process
trace_a = go.Scatter(x=data['Total_ticks'], y=data['ProcessA_ticks'], mode='lines+markers', name='Process A')
trace_b = go.Scatter(x=data['Total_ticks'], y=data['ProcessB_ticks'], mode='lines+markers', name='Process B')
trace_c = go.Scatter(x=data['Total_ticks'], y=data['ProcessC_ticks'], mode='lines+markers', name='Process C')

# Plot layout
layout = go.Layout(
    title='Lottery Scheduler Time Slices',
    xaxis=dict(title='Total Ticks'),
    yaxis=dict(title='Time Slices'),
    legend=dict(title='Processes')
)

# Plot the figure
fig = go.Figure(data=[trace_a, trace_b, trace_c], layout=layout)
fig.show()

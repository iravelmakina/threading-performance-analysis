import matplotlib.pyplot as plt
import csv

data = {}

with open("./data/threadPerformance.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        matrix_size = int(row[0])
        num_threads = int(row[1])
        time = float(row[2])

        if matrix_size not in data:
            data[matrix_size] = {"threads": [], "times": []}

        data[matrix_size]["threads"].append(num_threads)
        data[matrix_size]["times"].append(time)

plt.figure(figsize=(10, 6))

for matrix_size, values in data.items():
    plt.plot(
        values["threads"],
        values["times"],
        marker="o",
        label=f"{matrix_size}x{matrix_size}"
    )

    min_time = min(values["times"])
    min_index = values["times"].index(min_time)
    min_threads = values["threads"][min_index]

    plt.annotate(
        f"{min_threads}",
        (min_threads, min_time),
        textcoords="offset points",
        xytext=(0, 10),
        ha="center"
    )

plt.title("Thread Performance Scaling for Different Matrix Sizes")
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.xscale("log")
plt.yscale("log")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.legend(title="Matrix Size")
plt.tight_layout()

plt.savefig("./data/thread_scaling_graph.png")
plt.show()

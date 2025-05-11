from datasets import load_dataset

# This will download the entire 'train' split of the dataset
ds = load_dataset("clinc/clinc_oos", "plus" , split="train")

# Example: print the first example
print(ds)

# Optional: Save to disk
ds.to_csv("IP.csv")  # or to_json, to_parquet, etc.

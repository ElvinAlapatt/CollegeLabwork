import pandas as pd
data = {
    'students' : ["Elvin", "Abhay", "Athul", "KP","Aadithya"],
    'class' : ['A','B','A','A','B'],
    'subject': ['maths','maths','science','science','maths'],
    'marks': [95,85,98,75,100]
}
df = pd.DataFrame(data)
print("Original Data : ",df)
pivot_table = df.pivot_table(index='class',values='marks',columns='subject',aggfunc='mean')
print("\nPivot Table\n",pivot_table)
crosstable = pd.crosstab(index=df['class'],columns=df['marks'])
print("\nCross Table\n",crosstable)
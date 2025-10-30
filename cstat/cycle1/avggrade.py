student_grade = {
    "maths":93,
    "Physics":91,
    "English":98,
    "Chemistry":90,
    "Computer":99
}

def avg(d):
    if not d :
        return None
    total = sum(d.values())
    count = len(d)
    average = total / count
    return average

a = avg(student_grade)
print(a)
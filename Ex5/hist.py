from matplotlib import pyplot as plt
def main():
  a = []
  b = []
  with open("out.txt") as f:
    lines = f.readlines()
  for l in lines:
    i1,i2 = l.strip().split('=>')
    a.append(i1)
    b.append(int(i2)) 
  
  # print(a)
  #print(b)
  plt.style.use('ggplot')
  plt.bar(a,b)
  #plt.hist(b)
  plt.show()
if __name__ == "__main__":
  main()
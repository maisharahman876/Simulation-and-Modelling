import random
if __name__=="__main__":
    no_of_generation = int(input("Enter the number of generation: "))
    with open("input.txt") as f:
        input = f.read()
    #convert the string to array
    input = input.split()
    #convert the array to integer
    prob = [float(x) for x in input]
    #calculate cumulative probability
    cum_prob = [prob[0]]
    for i in range(1,len(prob)):
        cum_prob.append(cum_prob[i-1]+prob[i])
    
    # take a counter of size no_of_generation* 4
    counter = [[0 for x in range(5)] for y in range(no_of_generation)]
    for i in range(10000):
        parents=1
        
        for j in range(no_of_generation):
            total_children=0
            for k in range(parents):
                #generate a random number
                random_number = random.random()
                no_of_children=-1
                #find the index of the random number in the cumulative probability
                for i in range(len(cum_prob)):
                    if random_number <= cum_prob[i]:
                        no_of_children = i
                        break
                #increment the counter
                total_children += no_of_children
            if total_children<=4:
                counter[j][total_children] += 1
            parents = no_of_children
    for i in range(no_of_generation):
        print("Generation ",i+1)
        for j in range(5):
            print("Probability of ",j," neutrons is ",counter[i][j]/10000)

            
            
    
    

    

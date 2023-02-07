# marriage problem
import random
import matplotlib.pyplot as plt
population = 100
successes = [0 for x in range(population)]
success_criteria = 10 # this means the selected person must have rank 0
if __name__=="__main__":

    for i in range(10000):
        # geenrate a random population rank list 0 to population-1
        rank_list = list(range(population))
        # make it 2d list with 0 means not visited and 1 means  visited
        rank_list = [[x,0] for x in rank_list]
        # shuffle the list
        # vary the sample size
        # an array to store the success rate of size population to 0
        
        for sample_size in range(0,population):
            #choose a random sample of size sample_size with not visited and not duplicate
            sample = random.sample([x for x in rank_list if x[1]==0],sample_size)
            # mark the sample as visited and find the best rank
            best_rank = population-1
            for x in sample:
                x[1] = 1
                if x[0] < best_rank:
                    best_rank = x[0]
            #now check among the people outside the sample randomly
            selected_person = None
            for i in range(population-sample_size):
                # choose a random person
                person = random.choice([x for x in rank_list if x[1]==0])
                # mark the person as visited
                person[1] = 1
                # check if the person is better than the best rank
                if person[0] < best_rank:
                    selected_person = person
                    break
                #if it's the last person then select the person
                if i == population-sample_size-1:
                    selected_person = person
            #check if it is success
            if selected_person[0] < success_criteria:
                successes[sample_size] += 1
            #reset the visited flag
            for x in rank_list:
                x[1] = 0
    #print the success rate
    #plot successes/10000 vs sample size
    plt.plot([x/10000 for x in successes])
    plt.xlabel("Sample Size")
    plt.ylabel("Success Rate")
    #title = Succes criteria success_criteria
    plt.title("Success Criteria = "+str(success_criteria))
    plt.show()
    #save the plot
    plt.savefig("1705060_5a.png")

        
        




            
            
            





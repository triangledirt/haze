class trfSync {
    var tasks = [trfTask]()

    func addTask(task: trfTask) {
        tasks.append(task)
    }

    func synchronize() -> [trfBatch] {
    	// order by maximally resourced to minimally resourced
        // pick the first record, mark the first record
        // pick every record that uses any of the resources of the record
        // put them in a batch with the record
        // mark the record
        // record the height of the batch in expected duration
        // continue through the rest of the records, choosing the next record
        //   as the next master record, stopping adding to the current batch
        //   when its height in expected duration is just over the height of
        //   the first batch
        // have this return a set of arrays of not trfTask but of Ints that are
        //   task ids
        return [trfBatch]()
    }
}

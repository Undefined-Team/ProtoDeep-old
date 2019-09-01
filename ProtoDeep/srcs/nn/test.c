

output = csv_to_tensor(input);
for (size_t i = 0; i < network.len; i++)
{
    if (network.layer[i].rank == 2)
    {
        if (network.layer[i-1].rank == 2) // Dense
            output = get_output_dense(output, network.layer[i]);
        else if (network.layer[i-1].rank > 2) // Flatten
            output = get_output_dense(get_output_flatten(output), network.layer[i]);
    }
    else
    {
        if (network.layer[i-1].layer_type == "L_POOLING")
            output = get_output_pool(otuput, network.layer[i]);
        else if (network.layer[i-1].layer_type == "L_CONVOLUTION")
            output = get_output_conv(otuput, network.layer[i]);
    }
}
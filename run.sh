#!/bin/bash
java -jar ./modules/swagger-codegen-cli/target/swagger-codegen-cli.jar  generate -i friends.json --import-mappings EntityId=com.friends.transactionhandler.util.EntityId -c ./generator-config.json  -l spring -t ./modules/swagger-codegen/src/main/resources/JavaSpring/ -o /Users/wwadge/Documents/workspace/eft/friends-transaction-manager


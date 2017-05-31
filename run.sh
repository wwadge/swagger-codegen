#!/bin/bash
java -DdebugOperations2 -jar ./modules/swagger-codegen-cli/target/swagger-codegen-cli.jar  generate -i ~/Documents/friends-transaction-manager-backend-api/friends.yml --import-mappings MonetaryAmount=javax.money.MonetaryAmount,EntityId=com.friends.transactionhandler.util.EntityId -c ./generator-config.json  -l spring -t ./modules/swagger-codegen/src/main/resources/JavaSpring/ -o ~/Documents/swagger-codegen/friends-transaction-handler

